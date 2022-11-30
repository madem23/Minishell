/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:24:44 by antoine           #+#    #+#             */
/*   Updated: 2022/11/17 13:09:38 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

//Informs on the presence of pipes at the beginning
//and/or the end of the branch.
void	get_pipe_info(t_tree *branch, t_token *begin, t_token *end)
{
	if (begin->index == 0)
		branch->piped_input = false;
	else
		branch->piped_input = true;
	if (end->type == TK_PIPE)
		branch->piped_output = true;
	else
		branch->piped_output = false;
}

//Creates branches.
//Branch = part of cmd line before/after one pipe, or between 2 pipes.
//It is the bit of the tree that will be executed.
//Contains a maximum of one command.
//Branches are connected the their subtree. Only one branch per subtree.
t_tree	*create_branch(t_token *begin, t_token *end, t_tree *treetop,
	t_minishell *minishell)
{
	t_tree	*branch;

	branch = malloc(sizeof(t_tree));
	if (!branch)
		error(1, "Failed to allocate branch\n");
	branch->minishell = minishell;
	branch->first_token = begin;
	branch->treetop = treetop;
	branch->branch = NULL;
	branch->subtree = NULL;
	branch->nb_pipes = 0;
	branch->envp = NULL;
	get_pipe_info(branch, begin, end);
	branch->end_index = end->index;
	parsing_redir(branch);
	branch->here_doc = heredoc_parsing(begin, end->index,
			count_tk(begin, end->index, TK_DLOWER));
	parsing_cmd(branch);
	parsing_var_def(branch);
	return (branch);
}

//Creates subtrees.
//Subtree = subdivision of cmd line always starting at a pipe, ending at
//the end of the cmd line. All subtrees have ONE branch (first subdivision of
//subtree, until a pipe or EOF) and are linked to the next subtree.
t_tree	*create_subtree(t_token *begin, t_tree *treetop)
{
	t_tree	*subtree;

	subtree = malloc(sizeof(t_tree));
	if (!subtree)
		error(1, "Failed to allocate subtree\n");
	subtree->first_token = begin;
	subtree->treetop = treetop;
	subtree->branch = NULL;
	subtree->subtree = NULL;
	subtree->nb_pipes = count_tk(begin, -1, TK_PIPE);
	subtree->end_index = 0;
	subtree->exec_name = NULL;
	subtree->exec_args = NULL;
	subtree->exec_path = NULL;
	subtree->here_doc = -1;
	subtree->piped_input = true;
	subtree->piped_output = false;
	return (subtree);
}

//Counts the nb of token of the given type.
unsigned int	count_tk(t_token *first_token, int end_index, unsigned int type)
{
	size_t	nb;

	nb = 0;
	if (end_index >= 0)
	{
		while (first_token && first_token->index < end_index)
		{
			if (first_token->type == type)
				nb++;
			first_token = first_token->next_token;
		}
	}
	else
	{
		while (first_token)
		{
			if (first_token->type == type)
				nb++;
			first_token = first_token->next_token;
		}
	}
	return (nb);
}

//Initializes the treetop.
//Branches and subtrees will be created and linked later on.
t_tree	*tree_init(t_parser *parser)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		error(1, "Failed to allocate tree\n");
	tree->first_token = parser->first_token;
	tree->branch = NULL;
	tree->subtree = NULL;
	tree->treetop = NULL;
	tree->nb_pipes = count_tk(parser->first_token, -1, TK_PIPE);
	tree->end_index = 0;
	tree->exec_name = NULL;
	tree->exec_args = NULL;
	tree->exec_path = NULL;
	tree->envp = parser->envp;
	tree->nb_infiles = count_tk(parser->first_token, -1, TK_LOWER);
	tree->nb_outfiles = count_tk(parser->first_token, -1, TK_GREATER);
	tree->infiles = NULL;
	tree->outfiles = NULL;
	tree->here_doc = -1;
	return (tree);
}

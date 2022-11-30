/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:10:52 by antoine           #+#    #+#             */
/*   Updated: 2022/11/25 15:26:45 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

t_parser	*parser_init(t_lexer *lexer, t_minishell *minishell)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->current_token->next_token = NULL;
	parser->first_token = parser->current_token;
	parser->envp = minishell->envp;
	parser->cmd_paths = get_paths(minishell->var_def);
	return (parser);
}

t_parser	*lexing_start(t_parser *parser)
{
	while (parser->current_token->type != TK_EOC)
	{
		parser->current_token->next_token = lexer_get_next_token(parser->lexer);
		parser->current_token = parser->current_token->next_token;
		parser->current_token->next_token = NULL;
	}
	return (parser);
}

t_tree	*parser_start(t_parser *parser, t_minishell *minishell)
{
	t_tree	*top;

	expander(parser, minishell);
	top = tree_init(parser);
	parser->treetop = top;
	parser->treetop->paths = parser->cmd_paths;
	parsing(parser, minishell);
	return (top);
}


t_tree	*create_branch(t_token *begin, t_token *end, t_tree *treetop, t_minishell *minishell)
{
	t_tree	*branch;
	
	branch = malloc(sizeof(t_tree));
	if (!branch)
		error(1, "Failed to allocate branch\n");
	branch->minishell = minishell;
	branch->first_token = begin;
	branch->treetop = treetop;
	branch->branch = NULL; //pas de branche pour les branches
	branch->subtree = NULL; //pas de subtree pour les branches
	branch->nb_pipes = 0; //car dans branche
	branch->envp = NULL;
	if (begin->index == 0)
		branch->piped_input = false;
	else
		branch->piped_input = true;
	if (end->type == TK_PIPE)
		branch->piped_output = true;
	else
		branch->piped_output = false;
	branch->end_index = end->index;
	parsing_redir(branch);
	branch->here_doc = heredoc_parsing(begin, end->index, count_token_type(begin, end->index, TK_DLOWER));
	parsing_cmd(branch);
	parsing_var_def(branch);
	
	return (branch);
}

t_tree	*create_subtree(t_token *begin, t_tree *treetop)
{
	t_tree	*subtree;
	
	subtree = malloc(sizeof(t_tree));
	if (!subtree)
		error(1, "Failed to allocate subtree\n");
	subtree->first_token = begin;
	subtree->treetop = treetop;
	subtree->branch = NULL; //pour le moment
	subtree->subtree = NULL; //pour le moment
	subtree->nb_pipes = count_token_type(begin, -1, TK_PIPE);
	subtree->end_index = 0;
	subtree->exec_name = NULL; //name of cmd
	subtree->exec_args = NULL;// args and options of the said cmd
	subtree->exec_path = NULL; //path to execute cmd
	subtree->here_doc = -1;
	subtree->piped_input = true; //toujours vrai sinon pas de subtree
	subtree->piped_output = false;
	return (subtree);
}


t_tree	*parsing(t_parser *parser, t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*save_point;
	t_tree	*current_node;

	tmp = parser->first_token;
	save_point = tmp;
	current_node = parser->treetop;
	while (tmp)
	{
		if (tmp->type == TK_PIPE || tmp->type == TK_EOC)
		{
			current_node->branch = create_branch(save_point, tmp, parser->treetop, minishell);
			save_point = tmp;
		}
		if (tmp->type == TK_PIPE)
		{
			current_node->subtree = create_subtree(tmp->next_token, parser->treetop);
			current_node = current_node->subtree;
		}
		tmp = tmp->next_token;
	}
	return (NULL);
}

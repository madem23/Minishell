/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:10:52 by antoine           #+#    #+#             */
/*   Updated: 2022/11/09 18:13:41 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

t_parser	*parser_init(t_lexer *lexer, char *envp[])
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->current_token->next_token = NULL;
	parser->first_token = parser->current_token;
	parser->cmd_paths = get_paths(envp);
	return (parser);
}

t_tree	*parser_start(t_parser *parser)
{
	t_tree	*top;

	while (parser->current_token->type != TK_EOC)
	{
		parser->current_token->next_token = lexer_get_next_token(parser->lexer);
		parser->current_token = parser->current_token->next_token;
		parser->current_token->next_token = NULL;
	}
	top = tree_init(parser);
	parser->treetop = top;
	parsing(parser);
	return (top);
}


t_tree	*create_branch(t_token *begin, t_token *end)
{
	t_tree	*branch;
	
	branch = malloc(sizeof(t_tree));
	if (!branch)
		error(1, "Failed to allocate branch\n");
	branch->first_token = begin;
	branch->branch = NULL; //pas de branche pour les branches
	branch->subtree = NULL; //pas de subtree pour les branches
	branch->nb_pipes = 0; //car dans branche
	branch->end_index = end->index;
	parsing_redir(branch);
	parsing_cmd(branch);
	if (!branch->exec_args[0])
		branch->exec_name = NULL;
	else
		branch->exec_name = branch->exec_args[0]; //name of cmd
	branch->exec_args_size = 0; //a voir si utile
	if (count_token_type(begin, TK_DLOWER) > 0)
	{
		branch->here_doc = true;
		heredoc_parsing(begin, end->index);
	}
	else
	{
		branch->here_doc = false;
		//branch->content_here_doc = NULL;
	}
	if (begin->index == 0)
		branch->piped_input = false;
	else
		branch->piped_input = true;
	if (end->type == TK_PIPE)
		branch->piped_output = true;
	else
		branch->piped_output = false;
	return (branch);
}

t_tree	*create_subtree(t_token *begin)
{
	t_tree	*subtree;
	
	subtree = malloc(sizeof(t_tree));
	if (!subtree)
		error(1, "Failed to allocate subtree\n");
	subtree->first_token = begin;
	subtree->branch = NULL; //pour le moment
	subtree->subtree = NULL; //pour le moment
	subtree->nb_pipes = count_token_type(begin, TK_PIPE);
	subtree->end_index = 0;
	subtree->exec_name = NULL; //name of cmd
	subtree->exec_args = NULL;// args and options of the said cmd
	subtree->exec_path = NULL; //path to execute cmd
	subtree->exec_args_size = 0; //a voir si utile
	parsing_redir(subtree);
	if (count_token_type(begin, TK_DLOWER) > 0)
		subtree->here_doc = true;
	else
		subtree->here_doc = false;
	subtree->piped_input = true; //toujours vrai sinon pas de subtree
	subtree->piped_output = false;
	return (subtree);
}


t_tree	*parsing(t_parser *parser)
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
			current_node->branch = create_branch(save_point, tmp);
			save_point = tmp;
		}
		if (tmp->type == TK_PIPE)
		{
			current_node->subtree = create_subtree(tmp->next_token);
			current_node = current_node->subtree;
		}
		tmp = tmp->next_token;
	}
	return (NULL);
}
/*
void	parser_check_token(t_parser *parser, int token_type)
{
	int	current_token_type;

	current_token_type = parser->current_token->type;
	if (current_token_type == token_type)
	{
	}
	else
	{
		printf("Unexpected token %s of type %d\n", parser->current_token->value, parser->current_token->type);
		exit(1);
	}
}*/

t_var	*variable_init(char	*name, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->name = name;
	var->value = value;
	var->next = NULL;
	return (var);
}
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
#include "../expander/expander.h"
#include "../minishell.h"
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

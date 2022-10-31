/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:10:52 by antoine           #+#    #+#             */
/*   Updated: 2022/10/31 18:15:38 by antoine          ###   ########.fr       */
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
	parser->previous_token = NULL;
	parser->cmd_paths = get_paths(envp);
	
	return (parser);
}

t_tree	**parser_start(t_parser *parser)
{
	t_tree	**top;
	t_tree	*cmd_line;

	top = malloc(3 * sizeof(t_tree *));
	cmd_line = tree_init(TREE_CMD_LINE);
	top[0] = cmd_line;
	cmd_line->cmd_line_size++;
	while (parser->current_token->type != TK_EOC)
	{
		top[1] = parse(parser);
		cmd_line->cmd_line_size++;
		parser->previous_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	top[2] = NULL;

	return (top);
}

t_tree	*parse(t_parser *parser)
{
	if (parser->current_token->type == TK_WORD)
		return (parse_word(parser));
	if (parser->current_token->type == TK_EQUAL)
		return (parser_variable_definition(parser));
	return (NULL);
}

void	parser_check_token(t_parser *parser, int token_type)
{
	if (parser->current_token->type == token_type)
	{
		parser->previous_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	else
	{
		printf("Unexpected token %s of type %d\n", parser->current_token->value, parser->current_token->type);
		exit(1);
	}
}

t_tree	*parse_word(t_parser *parser)
{
	return (parse_execution(parser));
}

t_tree	*parse_execution(t_parser *parser)
{
	t_tree	*node;
	char	*exec_called;
	char	*exec_full_path;
	
	node = NULL;
	exec_called = parser->current_token->value;
	exec_full_path = check_exec_paths(parser->cmd_paths, exec_called);
	if (exec_full_path)
	{
			node = tree_init(TREE_EXEC_CALL);
			node->exec_name = parser->current_token->value;
			node->exec_path = exec_full_path;
			printf("parsed cmd: %s with path %s\n", exec_called, exec_full_path);
	}
	else
		node = tree_init(TREE_NULL);
	return (node);
}

t_tree		*parser_variable_definition(t_parser *parser)
{
	t_tree	*node;

	node = tree_init(TREE_VARIABLE_DEF);
	node->variable_name = parser->previous_token->value;
	parser_check_token(parser, TK_EQUAL);
	node->variable_value = parser->current_token->value;
	printf("parsed a var def where %s = %s\n", node->variable_name, node->variable_value);
	return (node);
}



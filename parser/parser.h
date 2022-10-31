/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:43:41 by antoine           #+#    #+#             */
/*   Updated: 2022/10/31 18:08:28 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "tree.h"
#include "../lexer/lexer.h"

typedef struct s_parser
{
	t_lexer		*lexer;
	t_token		*current_token;
	t_token		*previous_token;
	char		**cmd_paths;
}				t_parser;

t_parser	*parser_init(t_lexer *lexer, char *envp[]);

t_tree		**parser_start(t_parser *parser);

t_tree		*parse(t_parser *parser);

void		parser_check_token(t_parser *parser, int token_type);

t_tree		*parse_word(t_parser *parser);

t_tree		*parse_execution(t_parser *parser);

t_tree		*parser_variable_definition(t_parser *parser);

#endif
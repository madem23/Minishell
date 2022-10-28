/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:13:10 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/28 16:25:41 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

typedef struct s_lexer
{
	char	c;
	size_t	i;
	char	*cmd_line;
}				t_lexer;

t_lexer	*lexer_init(char *cmd_line);

void	lexer_read_next_char(t_lexer *lexer);

void	ignore_spaces(t_lexer *lexer);

t_token	*lexer_get_token(t_lexer *lexer);

char	*lexer_get_word(t_lexer *lexer);

char	*lexer_get_string(t_lexer *lexer);

char	*lexer_get_char(t_lexer *lexer);

#endif
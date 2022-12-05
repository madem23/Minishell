/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:13:10 by anloisea          #+#    #+#             */
/*   Updated: 2022/12/02 11:17:18 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

typedef struct s_lexer
{
	char	c;
	int		i;
	int		token_index;
	char	*cmd_line;
}				t_lexer;

t_lexer	*lexer_init(char *cmd_line);
void	lexer_read_next_char(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
void	ignore_spaces(t_lexer *lexer);
char	*lexer_get_word(t_lexer *lexer);
char	*lexer_get_string(t_lexer *lexer, char quote);
char	*lexer_get_char(t_lexer *lexer);
t_token	*token_init(int type, char *value, t_lexer *lexer);
char	*lexer_get_word(t_lexer *lexer);
char	*lexer_get_char(t_lexer *lexer);
char	*lexer_get_string(t_lexer *lexer, char quote);
int		count_char(char *s, int end_index);
int		count_char(char *s, int end_index);
void	ignore_spaces(t_lexer *lexer);

#endif
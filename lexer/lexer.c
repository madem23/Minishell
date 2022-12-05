/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:15:16 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/21 17:11:23 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

t_lexer	*lexer_init(char *cmd_line)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->cmd_line = cmd_line;
	lexer->i = 0;
	lexer->c = lexer->cmd_line[lexer->i];
	lexer->token_index = 0;
	return (lexer);
}

void	lexer_read_next_char(t_lexer *lexer)
{
	if (lexer->c != 0 || lexer->i < ft_strlen(lexer->cmd_line))
	{
		lexer->i++;
		lexer->c = lexer->cmd_line[lexer->i];
	}
}

t_token	*get_next_dollar_token(t_lexer *lexer)
{
	if (lexer->c == '$' && ft_isspace(lexer->cmd_line[lexer->i + 1]))
		return (token_init(TK_WORD, lexer_get_char(lexer), lexer));
	else
		return (token_init(TK_DOLLAR, lexer_get_word(lexer), lexer));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != 0 || lexer->i < ft_strlen(lexer->cmd_line))
	{
		if (ft_isspace(lexer->c))
			ignore_spaces(lexer);
		if (lexer->c == '|')
			return (token_init(TK_PIPE, lexer_get_char(lexer), lexer));
		else if (lexer->c == '>' && lexer->cmd_line[lexer->i + 1] == '>')
			return (token_init(TK_DGREATER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] == '<')
			return (token_init(TK_DLOWER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] != '<')
			return (token_init(TK_LOWER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '>' && lexer->cmd_line[lexer->i + 1] != '>')
			return (token_init(TK_GREATER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '$')
			return (get_next_dollar_token(lexer));
		else if (lexer->c == '"' || lexer->c == '\'')
			return (token_init(TK_QUOTE, lexer_get_word(lexer), lexer));
		else if (ft_isaccepted(lexer->c))
			return (token_init(TK_WORD, lexer_get_word(lexer), lexer));
		else
			return (token_init(TK_EOC, NULL, lexer));
	}
	return (token_init(TK_EOC, NULL, lexer));
}

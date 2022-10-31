/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:15:16 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/31 17:24:48 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*lexer_init(char *cmd_line)
{
	t_lexer	*lexer;
	
	lexer = malloc(sizeof(t_lexer));
	lexer->cmd_line = cmd_line;
	lexer->i = 0;
	lexer->c = lexer->cmd_line[lexer->i];
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

void	ignore_spaces(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
		lexer_read_next_char(lexer);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != 0 || lexer->i < ft_strlen(lexer->cmd_line))
	{
		if (ft_isspace(lexer->c))
			ignore_spaces(lexer);
		if (lexer->c == '\\')
			lexer_read_next_char(lexer);
		if (lexer->c == '|')
			return (token_init(TK_PIPE, lexer_get_char(lexer)));
		else if (lexer->c == '>' && lexer->cmd_line[lexer->i + 1] == '>')
			return (token_init(TK_DGREATER, lexer_get_char(lexer)));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] == '<')
			return (token_init(TK_DLOWER, lexer_get_char(lexer)));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] != '<')
			return (token_init(TK_LOWER, lexer_get_char(lexer)));
		else if (lexer->c == '>' && lexer->cmd_line[lexer->i + 1] != '>')
			return (token_init(TK_GREATER, lexer_get_char(lexer)));
		else if (lexer->c == '$')
			return (token_init(TK_DOLLAR, lexer_get_char(lexer)));
		else if (lexer->c == '=')
			return (token_init(TK_EQUAL, lexer_get_char(lexer)));
		// else if (lexer->c == '\'')
		// 	return (token_init(TK_SQUOTE, lexer_get_string(lexer)));
		else if (lexer->c == '"' )
			return (token_init(TK_STRING, lexer_get_string(lexer)));
		else if (ft_isaccepted(lexer->c))
			return (token_init(TK_WORD, lexer_get_word(lexer)));
		else
			lexer_read_next_char(lexer);
	}
	return (token_init(TK_EOC, "\0"));
}

char	*lexer_get_word(t_lexer *lexer)
{
	char	*str;
	int		i;
	
	str = malloc(1024 * sizeof(char));
	if (str == NULL)
		error(1, "failed to allocate string\n");
	i = 0;
	str[i] = 0;
	while (ft_isaccepted(lexer->c) && lexer->c != 0)
	{
		str[i] = lexer->c;
		i++;
		lexer_read_next_char(lexer);
	}
	str[i] = 0;
	
	return (str);
}

char *lexer_get_char(t_lexer *lexer)
{
	char *c;

	if (lexer->c == '<' && lexer->cmd_line[lexer-> i + 1] == '<')
	{
		c = malloc(3 * sizeof(char));
		c[0] = lexer->c;
		c[1] = lexer->cmd_line[lexer->i + 1];
		c[2] = 0;
		lexer_read_next_char(lexer);
		lexer_read_next_char(lexer);
		return (c);
	}
	if (lexer->c == '>' && lexer->cmd_line[lexer-> i + 1] == '>')
	{
		c = malloc(3 * sizeof(char));
		c[0] = lexer->c;
		c[1] = lexer->cmd_line[lexer->i + 1];
		c[2] = 0;
		lexer_read_next_char(lexer);
		lexer_read_next_char(lexer);
		return (c);
	}
	c = malloc(2 * sizeof(char));
	c[0] = lexer->c;
	c[1] = 0;
	lexer_read_next_char(lexer);

	return (c);
}

char	*lexer_get_string(t_lexer *lexer)
{
	char	*str;
	int		i;
	
	lexer_read_next_char(lexer);
	str = malloc(1024 * sizeof(char));
	if (str == NULL)
		error(1, "failed to allocate string\n");
	i = 0;
	str[i] = 0;
	while (lexer->c != '"')
	{
		str[i] = lexer->c;
		i++;
		lexer_read_next_char(lexer);
	}
	str[i] = 0;
	
	lexer_read_next_char(lexer);
	return (str);
}

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
		if (lexer->c == '|')
			return (token_init(TK_PIPE, lexer_get_char(lexer), lexer));
		else if (lexer->c == '>' && lexer->cmd_line[lexer->i + 1] == '>')
			return (token_init(TK_DGREATER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] == '<')
			return (token_init(TK_DLOWER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] == '>')
			return (token_init(TK_LOWER_GREATER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '<' && lexer->cmd_line[lexer->i + 1] != '<')
			return (token_init(TK_LOWER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '>' && lexer->cmd_line[lexer->i + 1] != '>')
			return (token_init(TK_GREATER, lexer_get_char(lexer), lexer));
		else if (lexer->c == '$' && ft_isspace(lexer->cmd_line[lexer->i + 1]))
			return (token_init(TK_WORD, lexer_get_char(lexer), lexer));
		else if (lexer->c == '$' && !ft_isspace(lexer->cmd_line[lexer->i + 1]))
			return (token_init(TK_DOLLAR, lexer_get_word(lexer), lexer));
		else if (lexer->c == '"' || lexer->c == '\'')
			return (token_init(TK_QUOTE, lexer_get_word(lexer), lexer));
		else if (ft_isaccepted(lexer->c))
			return (token_init(TK_WORD, lexer_get_word(lexer), lexer));
		else
			return (token_init(TK_EOC, NULL, lexer));
	}
	return (token_init(TK_EOC, NULL, lexer));
}

int	count_char(char *s, int end_index)
{
	int	i;

	i = 0;
	while (s[i] && i <= end_index)
		i++;
	return (i);
}

char	*lexer_get_word(t_lexer *lexer)
{
	char	*str;
	int		i;
	int size;
	
	size = count_char(lexer->cmd_line + lexer->i, ft_strlen(lexer->cmd_line) - 1);
	str = malloc((size + 1) * sizeof(char));
	str = ft_memset(str, 0, size + 1);
	if (str == NULL)
		error(1, "failed to allocate word\n");
	i = 0;
	while (lexer->c != 0 && ft_isaccepted(lexer->c))
	{
		if (lexer->c == '"' || lexer->c == '\'')
		{
			str[i]= '\0';
			ft_strcat(str, lexer_get_string(lexer, lexer->c));
			i = ft_strlen(str);
		}
		else
		{
			str[i] = lexer->c;
			i++;
			lexer_read_next_char(lexer);
		}
	}
	str[i] = 0;
	return (str);
}

char *lexer_get_char(t_lexer *lexer)
{
	char *c;

	if ((lexer->c == '<' && (lexer->cmd_line[lexer-> i + 1] == '<'
		|| lexer->cmd_line[lexer-> i + 1] == '>'))
		|| (lexer->c == '>' && lexer->cmd_line[lexer-> i + 1] == '>'))
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

//gets strings but does not remove quotes, must be parsed later on
char	*lexer_get_string(t_lexer *lexer, char quote)
{
	char	*str;
	int		i;

	i = 0;
	if (locate_char(lexer->cmd_line + lexer->i + 1, quote) < 0 
		|| lexer->cmd_line[lexer->i + 1] == '\0')
		quote = '\0';
	str = malloc(1024 * sizeof(char));
	if (str == NULL)
		error(1, "failed to allocate string\n");
	str[i++] = lexer->c;
	lexer_read_next_char(lexer);
	while (lexer->c && lexer->c != quote)
	{
		str[i] = lexer->c;
		i++;
		lexer_read_next_char(lexer);
	}
	if (quote != '\0')
		str[i++] = quote;
	str[i] = 0;
	lexer_read_next_char(lexer);
	return (str);
}

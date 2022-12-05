/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:09:06 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 15:09:08 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*lexer_get_word(t_lexer *lexer)
{
	char	*str;
	int		i;
	int		size;

	size = count_char(lexer->cmd_line + lexer->i,
			ft_strlen(lexer->cmd_line) - 1);
	str = malloc_string(size + 1);
	str = ft_memset(str, 0, size + 1);
	i = 0;
	while (lexer->c != 0 && ft_isaccepted(lexer->c))
	{
		if (lexer->c == '"' || lexer->c == '\'')
		{
			str[i] = '\0';
			ft_strcat(str, lexer_get_string(lexer, lexer->c));
			i = ft_strlen(str);
		}
		else
		{
			str[i++] = lexer->c;
			lexer_read_next_char(lexer);
		}
	}
	str[i] = 0;
	return (str);
}

char	*lexer_get_char(t_lexer *lexer)
{
	char	*c;

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

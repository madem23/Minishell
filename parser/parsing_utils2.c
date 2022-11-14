#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

char	*remove_closed_quotes(char *token_value, int *save, int *i, char *s)
{
	char	*tmp;
	char 	c;

	c = token_value[*save];
	while (token_value[*i])
	{
		if (token_value[*i] == c)
		{
			if (!s)
				s = ft_strjoin(ft_substr(token_value, 0, *save), ft_substr(token_value, *save + 1, *i - (*save + 1)));
			else
			{
				tmp = ft_strjoin(s, ft_substr(token_value, *save + 1, *i - (*save + 1)));
				free(s);
				s = tmp;
			}
			*save = *i;
			break ;
		}
		(*i)++;
	}
	if (!token_value[*i] && *save != *i)
		*i = *save;
	return (s);
}

char	*check_and_manage_closed_quotes(char *token_value, int *save, int *i, char *s)
{
	char	*tmp;

	if (s)
	{
		tmp = ft_strjoin(s, ft_substr(token_value, *save + 1, *i - (*save + 1)));
		free(s);
		s = tmp;
	}
	*save = (*i)++;
	s = remove_closed_quotes(token_value, save, i, s);
	return (s);
}

void	interpreting_closed_quotes(t_token *token)
{
	int	i;
	int	save;
	char	*s;
	char	*tmp;

	i = 0;
	save = 0;
	s = NULL;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
			s = check_and_manage_closed_quotes(token->value, &save, &i, s);
		if (token->value[i] == '\"')
			s = check_and_manage_closed_quotes(token->value, &save, &i, s);
		i++;
	}
	if (!token->value[i] && save != i && s)
	{
		tmp = ft_strjoin(s, ft_substr(token->value, save + 1, i - save));
		free(s);
		s = tmp;
	}
	if (s)
	{
		free(token->value);
		token->value = s;
	}
}

void	lexing_word_incl_dquotes(t_parser *parser)
{
	t_token	*tmp;

	tmp = parser->first_token;
	while (tmp)
	{
		if (tmp->type == TK_WORD)
			interpreting_closed_quotes(tmp);
		tmp = tmp->next_token;
	}
}

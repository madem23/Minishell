#include "parser.h"

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

char *interpreting_dollar_token(char *value, t_minishell *minishell)
{
	bool	convertion;
	char    *new_value;
	t_var	*var_tmp;

	convertion = false;
	new_value = NULL;
	var_tmp = minishell->var_def;
	while (var_tmp)
	{
		if (ft_strcmp(value, var_tmp->name) == 0)
		{
			new_value = ft_strdup(var_tmp->value);
			convertion = true;
		}
		var_tmp = var_tmp->next;
	}
	if (!var_tmp && convertion == false)
		new_value = ft_strdup("");
	return (new_value);
}

//locate the first occurence of any char of the charset in *s
int	ft_strchrset(const char *s, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (charset[j])
		{
			if (s[i] == charset[j])
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}


void	lexing_dollar_token(t_parser *parser, t_minishell *minishell)
{
	t_token	*tmp;
	int		i;
	int		i_occur;
	char	*tmp_s;

	i = 0;
	tmp = parser->first_token;
	while (tmp)
	{
		if (tmp->type == TK_DOLLAR)
		{
			i_occur = ft_strchrset(tmp->value, "!@#%^&*()_-+=[]{}:;.,?");
			if (tmp->value[1] == '{')
			{
				while (tmp->value[i] && tmp->value[i] != '}')
					i++;
				if (tmp->value[i])
				{
					tmp_s = ft_strjoin(interpreting_dollar_token(ft_substr(tmp->value, 2, i - 2), minishell), ft_strchr(tmp->value, '}') + 1);
					free(tmp->value);
					tmp->value = tmp_s;
				}
			}
			else if (i_occur >= 2)
			{
				tmp_s = ft_strjoin(interpreting_dollar_token(ft_substr(tmp->value, 1, i_occur - 1), minishell), tmp->value + i_occur);
				free(tmp->value);
				tmp->value = tmp_s;
			}
			else
			{
				tmp_s = interpreting_dollar_token(tmp->value + 1, minishell);
				free(tmp->value);
				tmp->value = tmp_s;
			}
		}
		tmp = tmp->next_token;
	}
}
#include "parser.h"

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

char *convert_dollar_token(char *value, t_minishell *minishell)
{
	bool	convertion;
	char    *new_value;
	t_var	*var_tmp;

	convertion = false;
	new_value = NULL;
	var_tmp = minishell->var_def;
	printf("value a convertir = %s\n", value);
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

char	*managing_curly_brakets(char *value, int i, t_minishell *minishell)
{
	char	*tmp_s;

	tmp_s = NULL; 
	while (value[i] && value[i] != '}')
		i++;
	if (value[i])
		tmp_s = ft_strjoin(convert_dollar_token(ft_substr(value, 2, i - 2), minishell), ft_strchr(value, '}') + 1);
	return (tmp_s);
}
/*
char *managing_non_alpha(char *value, int i, int j, t_minishell *minishell)
{
	char	*tmp_s;
	char	*tmp;
	char	*convert;

	tmp = ft_substr(value, 0, i);
	printf("Test non alpha, var a convertir = %s\n", tmp);
	convert = convert_dollar_token(tmp, minishell);
	printf("Test non alpha, convert = %s\n", convert);
	tmp_s = ft_strjoin(convert, value + j);
	printf("Test non alpha, RES FINAL = %s\n", tmp_s);
	return (tmp_s);
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
			i_occur = ft_strchrset(tmp->value, "\"\'!@#^%&*()-+=[]{}:;.,?");
			if (tmp->value[1] == '{')
				tmp_s = managing_curly_brakets(tmp->value, i, minishell);
			else if (tmp->value[1] >= '0' && tmp->value[1] <= '9')
				tmp_s = managing_non_alpha(tmp->value, 2, 2, minishell);
			else if (i_occur == 1)
			{
				if (tmp->value[1] == '\'' || tmp->value[1] == '"')
				{
					if (locate_char(tmp->value + 2, tmp->value[1]) >= 0)
						interpreting_closed_quotes(&tmp->value, minishell);
				}
				else
					break;
			}
			else if (i_occur >= 2)
			{
				if (tmp->value[i_occur] == '\'' || tmp->value[i_occur] == '"')
				{
					if (locate_char(tmp->value + i_occur + 1, tmp->value[i_occur]) >= 0)
						interpreting_closed_quotes(&tmp->value, minishell);
				}
				else
					tmp_s = managing_non_alpha(tmp->value, i_occur - 1, i_occur, minishell);
			}
			else
			{
				tmp_s = convert_dollar_token(tmp->value + 1, minishell);
			}
				free(tmp->value);
				tmp->value = tmp_s;
		}
		tmp = tmp->next_token;
	}
}*/
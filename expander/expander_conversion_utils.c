/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_conversion_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:03:33 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:03:37 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
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

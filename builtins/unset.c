/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:33:01 by antoine           #+#    #+#             */
/*   Updated: 2022/12/22 11:29:56 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	rmv_var_from_list(t_var	**list, t_var *var)
{
	t_var	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->next == var)
		{
			free(var->name);
			free(var->value);
			tmp->next = var->next;
			free(var);
		}
		tmp = tmp->next;
	}
}

int	unset(char **args, t_minishell *minishell)
{
	t_var	*tmp;

	g_global.u->i = -1;
	while (args[++(g_global.u->i)])
	{
		if (ft_strchrset(args[g_global.u->i], "\"\'!@#^%&*()- +[]{}:;.,?") != -1
			|| ft_isdigit(args[g_global.u->i][0]))
		{
			ft_putstr_fd("minishell: unset: \'", 2);
			ft_putstr_fd(args[g_global.u->i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (1);
		}
		tmp = minishell->var_def;
		while (tmp)
		{
			if (!ft_strcmp(args[g_global.u->i], tmp->name))
			{
				rmv_var_from_list(&minishell->var_def, tmp);
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

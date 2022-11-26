/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:12:36 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 16:35:51 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(t_var *list, char **args)
{
	int		i;
	t_var	*tmp;

	tmp = list;
	if (tab_len(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			ft_putstr_fd("env: invalid option -- \"", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("\"\n", 2);
			i++;
		}
		ft_putstr_fd("usage: env\n", 2);
		return (125);
	}
	i = 0;
	while (tmp)
	{
		if (tmp->env == true)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

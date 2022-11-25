/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:12:36 by antoine           #+#    #+#             */
/*   Updated: 2022/11/18 15:58:13 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env(char **envp, char **args)
{
	int	i;

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
		return ;
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

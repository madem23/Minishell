/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:07:41 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 11:31:43 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (!args || !args[1])
		exit(0);
	else if (tab_len(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(1);
	}
	else
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				exit_error(args[1]);
			i++;
		}
		exit(ft_atoi(args[1]));
	}
}

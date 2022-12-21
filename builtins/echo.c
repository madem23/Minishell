/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:21:51 by antoine           #+#    #+#             */
/*   Updated: 2022/12/21 10:21:39 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	look_for_intruder(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	echo(char **args)
{
	int	i;

	i = 1;
	if (tab_len(args) == 1)
		printf("\n");
	if (!args[i])
		return (0);
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		if (args[i + 1] && look_for_intruder(args[i] + 1, 'n'))
			break ;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(args[1], "-n", 2))
		printf("\n");
	return (0);
}

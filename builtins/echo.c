/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:21:51 by antoine           #+#    #+#             */
/*   Updated: 2022/11/17 11:54:40 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(char **args)
{
	int	i;

	if (tab_len(args) == 1)
		printf("\n");
	if (!ft_strncmp(args[1], "-n", 2))
		i = 2;
	else
		i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(args[1], "-n", 2))
		printf("\n");
}

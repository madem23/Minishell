/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:21:51 by antoine           #+#    #+#             */
/*   Updated: 2022/11/14 12:09:16 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//args[0] = cmd
//args[1] = option

void	echo(char **args)
{
	int	i;
	
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(args[1], "-n", 2))
		i = 2;		// we start to print after -n
	else
		i = 1;		// we print all after "echo"
	while(args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(args[1], "-n", 2))
		printf("\n");
}
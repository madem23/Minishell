/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:21:51 by antoine           #+#    #+#             */
/*   Updated: 2022/11/15 17:05:02 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"



int	main(int argc, char *argv[])
{
	int	i;

	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(argv[1], "-n", 2))
		i = 2;
	else
		i = 1;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 2))
		printf("\n");
	return (0);
}

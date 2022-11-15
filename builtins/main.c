/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:00:17 by antoine           #+#    #+#             */
/*   Updated: 2022/11/15 13:03:54 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	int value = execve("/home/antoine/42cursus/v6/builtins/echo", argv + 1, NULL);
	if (value == -1)
		perror("main:");
	return (1);
}
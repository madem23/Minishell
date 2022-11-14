/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:50:05 by antoine           #+#    #+#             */
/*   Updated: 2022/11/14 15:18:42 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
	int pid = fork();
	if (pid == 0)
	{
		pwd();
		cd(argv[1], envp);
		sleep(2);
		pwd();
	}
	waitpid(pid, NULL, 0);
	//pwd();
	//echo(argv);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/16 12:59:02 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd(char **args)
{
	int		value;
	char	*path;

	puts(args[1]);
	if (tab_len(args) == 1)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
	}
	else if (args[1][0] == '/')
		path = args[1];
	else
		path = ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), args[1]);
	value = chdir(path);
	if (value == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return ;
	}
	pwd();
}

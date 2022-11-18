/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/18 13:15:39 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//join to fix
char	*get_home_var(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "HOME=", 5))
			home = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		i++;
	}
	return (home);
}

void	cd(char **args, char **envp)
{
	int		value;
	char	*path;

	if (tab_len(args) == 1)
	{
		path = get_home_var(envp);
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
	free(path);
}

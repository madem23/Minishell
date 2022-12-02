/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/12/02 11:27:55 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd(char **args, t_minishell *minishell)
{
	char	*path;
	char	*home;
	char	*newpwd;

	if (tab_len(args) == 1)
	{
		path = get_var_value(minishell->var_def, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (args[1][0] == '~')
	{
		home = get_var_value(minishell->var_def, "HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		path = ft_strjoin(home, args[1] + 1);
		free(home);
	}
	else if (args[1][0] == '-' && !args[1][1])
	{
		path = get_var_value(minishell->var_def, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = ft_strdup(args[1]);
	newpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(path);
		free(newpwd);
		return (1);
	}
	change_var_value(minishell->var_def, "OLDPWD", newpwd);
	free(path);
	return (0);
}

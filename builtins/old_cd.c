/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_sick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/12/15 15:52:15 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*error_var_not_set(char *var)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(" not set\n", 2);
	return (NULL);
}

char	*get_path_for_cd(char *path, char **args, t_minishell *minishell)
{
	char	*home;

	if (tab_len(args) == 1)
	{
		path = get_var_value(minishell->var_def, "HOME");
		if (!path)
			return (error_var_not_set("HOME"));
	}
	else if (args[1][0] == '~')
	{
		home = get_var_value(minishell->var_def, "HOME");
		if (!home)
			return (error_var_not_set("HOME"));
		path = ft_strjoin(home, args[1] + 1);
		free(home);
	}
	else if (args[1][0] == '-' && !args[1][1])
	{
		path = get_var_value(minishell->var_def, "OLDPWD");
		if (!path)
			return (error_var_not_set("OLDPWD"));
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

int	cd(char **args, t_minishell *minishell)
{
	char	*newpwd;
	char	*path;
	
	if (tab_len(args) > 2)
	{
		ft_putstr_fd("minishell: cd : too many arguments\n", 2);
		return (1);
	}
	path = NULL;
	path = get_path_for_cd(path, args, minishell);
	if (path == NULL)
		return (1);
	if (args[1] && args[1][0] == '-' && !args[1][1])
		printf("%s\n", path);
	newpwd = get_var_value(minishell->var_def, "PWD");
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(path);
		free(newpwd);
		return (1);
	}
	else
		change_var_value(minishell->var_def, "OLDPWD", newpwd);
		change_var_value(minishell->var_def, "PWD", getcwd(NULL, 0));
	if (!newpwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		change_var_value(minishell->var_def, "OLDPWD", get_var_value(minishell->var_def, "PWD"));
		change_var_value(minishell->var_def, "PWD", ft_strjoin(get_var_value(minishell->var_def, "PWD"), ft_strjoin("/", args[1])));
		return (0);
	}
	free(path);
	return (0);
}

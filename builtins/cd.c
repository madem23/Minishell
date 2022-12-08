/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 17:09:44 by antoine          ###   ########.fr       */
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

	path = NULL;
	path = get_path_for_cd(path, args, minishell);
	if (path == NULL)
		return (1);
	if (args[1][0] == '-' && !args[1][1])
		printf("%s\n", path);
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

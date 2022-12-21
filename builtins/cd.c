/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:52:28 by antoine           #+#    #+#             */
/*   Updated: 2022/12/21 15:41:09 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	error_retreiving(t_minishell *minishell)
{
	char	*cwd;
	char	*tmp;

	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	tmp = (get_var_value(minishell->var_def, "OLDPWD"));
	cwd = ft_strjoin(tmp, "./..");
	free(tmp);
	change_var_value(minishell->var_def, "PWD", cwd);
	free(cwd);
	return (0);
}

int	change_cwd(t_minishell *minishell)
{
	char	*cwd;

	cwd = get_var_value(minishell->var_def, "PWD");
	if (cwd && !change_var_value(minishell->var_def, "OLDPWD", cwd))
		var_add_back(&minishell->var_def,
			var_init(ft_strdup("OLDPWD"), ft_strdup(cwd), true));
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (error_retreiving(minishell));
	else
	{
		if (!change_var_value(minishell->var_def, "PWD", cwd))
			var_add_back(&minishell->var_def,
				var_init(ft_strdup("PWD"), ft_strdup(cwd), true));
		free(cwd);
	}
	return (1);
}

void	*error_var_not_set(char *var)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(" not set\n", 2);
	return (NULL);
}

char	*check_for_path(char **args, t_minishell *minishell)
{
	char	*path;
	char	*tmp;

	if (tab_len(args) == 1 || args[1][0] == '~')
	{
		tmp = get_var_value(minishell->var_def, "HOME");
		if (!tmp)
			return (error_var_not_set("HOME"));
		if (args[1])
			path = ft_strjoin(tmp, args[1] + 1);
		else
			path = get_var_value(minishell->var_def, "HOME");
		free(tmp);
	}
	else if (!ft_strcmp("-", args[1]))
	{
		path = get_var_value(minishell->var_def, "OLDPWD");
		if (!path)
			return (error_var_not_set("OLDPWD"));
		printf("%s\n", path);
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

int	cd(char **args, t_minishell *minishell)
{
	char	*path;
	int		exit;

	if (tab_len(args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = check_for_path(args, minishell);
	if (!path)
		return (1);
	if (!chdir(path))
	{
		if (!change_cwd(minishell))
			exit = 0;
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		exit = 1;
	}
	free(path);
	return (exit);
}

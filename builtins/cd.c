/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:52:28 by antoine           #+#    #+#             */
/*   Updated: 2022/12/20 11:54:06 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd(char **args, t_minishell *minishell)
{
	char	*path;
	char	*tmp;
	char	*cwd;

	if (tab_len(args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (tab_len(args) == 1)
	{
		path = get_var_value(minishell->var_def, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (!ft_strcmp("-", args[1]))
	{
		path = get_var_value(minishell->var_def, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		printf("%s\n", path);
	}
	else if (args[1][0] == '~')
	{
		tmp = get_var_value(minishell->var_def, "HOME");
		if (!tmp)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		path = ft_strjoin(tmp, args[1] + 1);
		free(tmp);
	}
	else
			path = ft_strdup(args[1]);
	if(!chdir(path))
	{
		change_var_value(minishell->var_def, "OLDPWD", get_var_value(minishell->var_def, "PWD"));
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			tmp = (get_var_value(minishell->var_def, "OLDPWD"));
			change_var_value(minishell->var_def, "PWD", ft_strjoin(tmp, "/.."));
			free(tmp);
			free(path);
			return (0);
		}
		else
			change_var_value(minishell->var_def, "PWD", cwd);
		free(path);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	return (0);
}
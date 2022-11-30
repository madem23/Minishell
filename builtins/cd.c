/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 20:17:12 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//join to fix
// cd /

int	cd(char **args, t_minishell *minishell)
{
	char	*path;
	char	*home;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_var_value(minishell->var_def, "OLDPWD");
	if (!oldpwd)
		var_add_back(&minishell->var_def, var_init(ft_strdup("OLDPWD"), getcwd(NULL, 0), true));
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
		path = ft_strjoin(home, args[1] + 1);
		free(home);
	}
	else if (args[1][0] == '-' && !args[1][1])
	{
		path = oldpwd;
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
	change_var_value(minishell->var_def, "OLDPWD", newpwd);
	free(newpwd);
	if (chdir(path) == -1)
	{
		change_var_value(minishell->var_def, "OLDPWD", oldpwd);
		free(oldpwd);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 18:48:15 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//join to fix
// cd /
char	*get_variable_value(t_var *var_list, char *name)
{
	t_var	*tmp;
	char	*value;

	tmp = var_list;
	value = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			value = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (value);
}

int	cd(char **args, t_minishell *minishell)
{
	char	*path;
	char	*home;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_variable_value(minishell->var_def, "OLDPWD");
	if (tab_len(args) == 1)
	{
		path = get_variable_value(minishell->var_def, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (args[1][0] == '~')
	{
		home = get_variable_value(minishell->var_def, "HOME");
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
	change_variable_value(minishell->var_def, "OLDPWD", newpwd);
	free(newpwd);
	if (chdir(path) == -1)
	{
		change_variable_value(minishell->var_def, "OLDPWD", oldpwd);
		free(oldpwd);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

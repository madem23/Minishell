/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/25 13:02:29 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//join to fix
// cd /
char	*get_home_var(t_var *var_list)
{
	t_var	*tmp;
	char	*home;

	tmp = var_list;
	home = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
			home = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (home);
}

int	cd(char **args, t_minishell *minishell)
{
	int		value;
	char	*path;
	char	*home;

	if (tab_len(args) == 1)
	{
		path = get_home_var(minishell->var_def);
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (args[1][0] == '~')
	{
		home = get_home_var(minishell->var_def);
		path = ft_strjoin(home, args[1] + 1);
		free(home);
	}
	else
		path = ft_strdup(args[1]);
	value = chdir(path);
	if (value == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

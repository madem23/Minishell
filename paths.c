/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:23:17 by antoine           #+#    #+#             */
/*   Updated: 2022/11/25 15:36:03 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_var *var_list)
{
	char	*env_path;
	char	**paths;
	char	*tmp;
	t_var	*tmp_list;
	int		i;

	env_path = NULL;
	tmp_list = var_list;
	while (tmp_list)
	{
		if (ft_strnstr(tmp_list->name, "PATH", 4))
			env_path = ft_strdup(tmp_list->value);
		tmp_list = tmp_list->next;
	}
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free (env_path);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	*check_exec_paths(char **paths, char *exec_called)
{
	int		i;
	char	*full_exec_path;

	if (!exec_called)
		return (NULL);
	if (access(exec_called, F_OK) == 0)
		return (ft_strdup(exec_called));
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_exec_path = ft_strjoin(paths[i], exec_called);
		if (access(full_exec_path, F_OK) == 0)
			return (full_exec_path);
		free(full_exec_path);
		i++;
	}
	return (NULL);
}

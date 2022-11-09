/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:23:17 by antoine           #+#    #+#             */
/*   Updated: 2022/11/09 17:46:08 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char *envp[])
{
	char	*env_path;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		i++;
	}
	if (!env_path)
		error(1, "could find env PATH\n");
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

	if (access(exec_called, F_OK) == 0)
		return (exec_called);
	i = 0;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/14 16:05:14 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd(const char *path, char *envp[])
{
	int		value;
	int		i;
	char	*home;

	home = NULL;
	if (!path)
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "HOME=", 5))
				home = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			i++;
		}
		if (!home)
			error(1, "cd : HOME not set\n");
		chdir(home);
		free(home);
	}
	else
	{
		value = chdir(path);
		if (value == -1)
			perror(path);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by antoine           #+#    #+#             */
/*   Updated: 2022/11/15 17:18:49 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char *argv[])
{
	int		value;
	char	*path;

	if (argc == 1)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), argv[1]);
	value = chdir(path);
	if (value == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

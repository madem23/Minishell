/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:07:53 by antoine           #+#    #+#             */
/*   Updated: 2022/11/16 12:57:08 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_builtins(t_tree *branch)
{
	if (!ft_strncmp(branch->exec_name, "echo", ft_strlen(branch->exec_name)))
	{
		echo(branch->exec_args);
		return (1);
	}
	else if (!ft_strncmp(branch->exec_name, "pwd", ft_strlen(branch->exec_name)))
	{
		pwd();
		return (1);
	}
	else if (!ft_strncmp(branch->exec_name, "cd", ft_strlen(branch->exec_name)))
	{
		cd(branch->exec_args);
		return (1);
	}
	else if (!ft_strncmp(branch->exec_name, "env", ft_strlen(branch->exec_name)))
	{
		env(branch->envp, branch->exec_args);
		return (1);
	}
	// else if (!ft_strncmp(branch->exec_name, "export", ft_strlen(branch->exec_name)))
	// 	return(1);
	// else if (!ft_strncmp(branch->exec_name, "unset", ft_strlen(branch->exec_name)))
	// 	return(1);
	else
		return (0);
}
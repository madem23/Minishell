/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:07:53 by antoine           #+#    #+#             */
/*   Updated: 2022/11/17 14:38:17 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_builtins(t_tree *branch, t_minishell *minishell)
{
	if (!ft_strcmp(branch->exec_name, "echo"))
	{
		echo(branch->exec_args);
		return (1);
	}
	else if (!ft_strcmp(branch->exec_name, "pwd"))
	{
		pwd();
		return (1);
	}
	else if (!ft_strcmp(branch->exec_name, "cd"))
		return (1);
	else if (!ft_strcmp(branch->exec_name, "env"))
	{
		env(branch->treetop->envp, branch->exec_args);
		return (1);
	}
	else if (!ft_strcmp(branch->exec_name, "export"))
	{
		export(branch->exec_args, branch->treetop->envp, minishell);
		return (1);	
	}
	// else if (!ft_strcmp(branch->exec_name, "unset"))
	// 	return(1);
	else
		return (0);
}
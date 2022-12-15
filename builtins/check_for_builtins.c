/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:07:53 by antoine           #+#    #+#             */
/*   Updated: 2022/12/15 15:36:08 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_builtins(t_tree *branch, t_minishell *minishell)
{
	if (!ft_strcmp(branch->exec_name, "echo"))
		return (echo(branch->exec_args));
	else if (!ft_strcmp(branch->exec_name, "pwd"))
		return (pwd(minishell));
	else if (!ft_strcmp(branch->exec_name, "cd"))
		return (1);
	else if (!ft_strcmp(branch->exec_name, "env"))
		return (env(minishell->var_def, branch->exec_args));
	else if (!ft_strcmp(branch->exec_name, "export"))
		return (1);
	else if (!ft_strcmp(branch->exec_name, "unset"))
		return (1);
	else if (!ft_strcmp(branch->exec_name, "exit"))
		return (1);
	else
		return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:38:24 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/25 15:30:00 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	error(int errnum, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	exit(errnum);
}

void	error_too_many_pipes(t_minishell *minishell)
{
	perror("Too many pipes");
	free_parser(minishell->parser);
	exit(EXIT_FAILURE);
}

void	error_cmd_not_found(t_minishell *minishell, t_tree *branch,
		int **pipefd)
{
	ft_putstr_fd(branch->exec_name, 2);
	write(2, ": command not found\n", 20);
	free_end_executor(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	exit(EXIT_FAILURE);
}

void	error_cmd_path(t_minishell *minishell, t_tree *branch, int **pipefd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(branch->exec_name, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	free_end_executor(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	exit(EXIT_FAILURE);
}

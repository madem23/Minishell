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

void	error_cmd_not_found(t_minishell *minishell, t_tree *branch, int **pipefd)
{
	ft_putstr_fd(branch->exec_name, 2);
	write(2, ": command not found\n", 20);
	free_end_pipex(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	exit(EXIT_FAILURE);
}

void	error_cmd_path(t_minishell *minishell, t_tree *branch, int **pipefd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(branch->exec_name, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	free_end_pipex(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	exit(EXIT_FAILURE);
}
/*
void	error_empty_cmd(char *cmd, t_global global, int x, int **pipefd)
{
	if (x != 1 || global.input->fd_infile != -1)
	{
		write(2, "permission denied: ", 19);
		ft_putstr_fd(cmd, 2);
		write(2, "\n", 1);
	}
	free_parsing(global);
	free_pipex(global, pipefd);
	exit(EXIT_FAILURE);
}

void	error_exec(char *str, char **cmd, int **pipefd, t_global global)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 2);
		write(2, " ", 1);
		i++;
	}
	ft_putstr_fd(": failure of execve call (", 2);
	ft_putstr_fd(str, 2);
	write(2, ")\n", 2);
	free_parsing(global);
	free_pipex(global, pipefd);
	exit(EXIT_FAILURE);
}*/
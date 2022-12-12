/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpolpa <elpolpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:38:24 by anloisea          #+#    #+#             */
/*   Updated: 2022/12/10 10:26:18 by elpolpa          ###   ########.fr       */
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
	if (ft_strlen(branch->exec_name) >= 2)
	{
		if ((branch->exec_name[0] == '.' && branch->exec_name[1] == '/')
			|| branch->exec_name[0] == '/')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			write(2, ": command not found\n", 20);
	}
	else
		write(2, ": command not found\n", 20);
	free_end_executor(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	exit(127);
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

int	check_ambi_redir(char *value, int *fd)
{
	int	i;

	i = 0;
	while (value[i] && !ft_isspace(value[i]))
		i++;
	while (value[i] && ft_isspace(value[i]))
		i++;
	if ((i != 0 && value[i] != '\0') || value[0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		g_global.ambi_redir = true;
		*fd = -1;
		return (0);
	}
	return (1);
}

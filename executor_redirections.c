/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:43:31 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 17:43:32 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

//branch->heredoc : last_index
/* Checks for the last input redir and amends fd[0] if necessary
(if no error on file, otherwise fd[0] = -1).
If heredoc after last input redir, replaces fd[0]. */
int	*check_input_redir(t_tree *branch, int *fd)
{
	int	i;

	i = 0;
	while (branch->infiles[i])
	{
		fd[0] = open(branch->infiles[i]->value, O_RDONLY);
		if (fd[0] == -1)
		{
			perror(branch->infiles[i]->value);
			break ;
		}
		i++;
	}
	if (fd[0] != -1 && ((i == 0 && branch->here_doc >= 0)
			|| (i >= 1 && branch->here_doc >= 0
				&& branch->infiles[i - 1]->index < branch->here_doc)))
	{
		if (count_tk(branch->first_token, branch->end_index, TK_DLOWER) > 1)
			fd[0] = open("empty_heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 777);
		else
			fd[0] = open("tmp_heredoc.txt", O_RDONLY);
	}
	return (fd);
}

/* Checks for the last regular output and amends fd[1] if necessary. */
int	*check_output_redir(t_tree *branch, int *fd)
{
	int	i;

	i = 0;
	while (branch->outfiles[i] && ((fd[0] == -1
				&& branch->outfiles[i]->index < branch->infiles[i]->index)
			|| (fd[0] >= 0)))
	{
		fd[1] = open(branch->outfiles[i]->value,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] == -1)
		{
			perror(branch->outfiles[i]->value);
			break ;
		}
		i++;
	}
	return (fd);
}

/* Checks for the last output among output redir in append mode
and amends fd[1] if necessary. */
int	*check_output_append_redir(t_token **app_outfiles,
	t_token **infiles, int *fd)
{
	int	i;

	i = 0;
	while (app_outfiles[i] && ((fd[0] == -1
				&& app_outfiles[i]->index < infiles[i]->index)
			|| (fd[0] >= 0)))
	{
		fd[1] = open(app_outfiles[i]->value,
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd[1] == -1)
		{
			perror(app_outfiles[i]->value);
			break ;
		}
		i++;
	}
	return (fd);
}

/* Initializes a tab of 2 fds, tab[0] = infile, tab[1] = output. */
int	*check_redir_open_files(t_tree *branch)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	fd = check_input_redir(branch, fd);
	fd = check_output_redir(branch, fd);
	fd = check_output_append_redir(branch->outfiles_append,
			branch->infiles, fd);
	return (fd);
}

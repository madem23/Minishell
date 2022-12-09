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
int	*check_input_redir(t_tree *branch, int *fd, int *i)
{
	while (branch->infiles[*i])
	{
		if (fd[0] != 0)
			close(fd[0]);
		fd[0] = open(branch->infiles[*i]->value, O_RDONLY);
		if (fd[0] == -1)
		{
			perror(branch->infiles[*i]->value);
			break ;
		}
		(*i)++;
	}
	if (fd[0] != -1 && ((*i == 0 && branch->here_doc >= 0)
			|| (*i >= 1 && branch->here_doc >= 0
				&& branch->infiles[(*i) - 1]->index < branch->here_doc)))
	{
		if (count_tk(branch->first_token, branch->end_index, TK_DLOWER) > 1)
			fd[0] = open("empty_heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 777);
		else
			fd[0] = open("tmp_heredoc.txt", O_RDONLY);
	}
	return (fd);
}

/* Checks for the last regular output and amends fd[1] if necessary. */
int	*check_output_redir(t_tree *branch, int *fd, int *j, int i)
{
	while (branch->outfiles[*j] && ((fd[0] == -1
				&& branch->outfiles[*j]->index < branch->infiles[i]->index)
			|| (fd[0] >= 0)))
	{
		if (fd[1] > 0)
			close(fd[1]);
		fd[1] = open(branch->outfiles[*j]->value,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] == -1)
		{
			perror(branch->outfiles[*j]->value);
			break ;
		}
		(*j)++;
	}
	(*j)--;
	return (fd);
}

/* Checks for the last output among output redir in append mode
and amends fd[1] if necessary. */
int	*check_output_append_redir(t_tree *branch, int *fd, int j, int i)
{
	int	k;
	int	secu;

	k = 0;
	secu = 0;
	while (branch->outfiles_append[k]
		&& ((fd[0] == -1 && branch->outfiles_append[k]->index < branch->infiles[i]->index) || (fd[0] >= 0)))
	{
		if (fd[1] == 0 || (fd[1] > 0 && branch->outfiles[j]->index < branch->outfiles_append[k]->index))
		{
			if (fd[1] > 0)
				close(fd[1]);
			fd[1] = open(branch->outfiles_append[k]->value, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (fd[1] == -1)
			{
				perror(branch->outfiles_append[k]->value);
				break ;
			}
		}
		else
		{
			secu = open(branch->outfiles_append[k]->value, O_CREAT | O_RDWR | O_APPEND, 0644);
			close(secu);
		}
		k++;
	}
	return (fd);
}

/* Initializes a tab of 2 fds, tab[0] = infile, tab[1] = output. */
int	*check_redir_open_files(t_tree *branch)
{
	int	*fd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	fd = check_input_redir(branch, fd, &i);
	fd = check_output_redir(branch, fd, &j, i);
	fd = check_output_append_redir(branch, fd, j, i);
	if (fd[0] < 0 || fd[1] < 0 || !branch->exec_name)
		exit(EXIT_FAILURE);
	return (fd);
}

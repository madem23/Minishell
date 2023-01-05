/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:04:33 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/05 14:27:55 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h"

int	heredoc_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token '%s'\n", s);
	return (0);
}

int	find_last_heredoc(t_token *first_token, int end_index)
{
	int		index_last;
	t_token	*tmp;

	tmp = first_token;
	index_last = 0;
	while (tmp && tmp->index < end_index)
	{
		if (tmp->e_tk_type == TK_DLOWER)
			index_last = tmp->index;
		tmp = tmp->next_token;
	}
	return (index_last);
}

int	fill_heredoc(t_token *tmp, int index_last)
{
	char	*limiter;
	int		fd;
	char	*line;

	limiter = tmp->next_token->value;
	fd = open("tmp_heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 777);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strnstr(line, limiter, ft_strlen(limiter))
			&& line[ft_strlen(limiter)] == '\n')
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
	return (index_last);
}

void	heredoc_parsing_sigint(t_token *tmp, int index_last)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		g_global.minishell->sa.sa_handler = &handler_sigint_heredoc;
		sigaction(SIGINT, &g_global.minishell->sa, NULL);
		fill_heredoc(tmp, index_last);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &g_global.exit_status, 0);
		if (WIFEXITED(g_global.exit_status)
			&& WEXITSTATUS(g_global.exit_status) == 130)
		{
			g_global.exit_status = 130;
			g_global.sigint_heredoc = true;
		}
	}
}

int	heredoc_parsing(t_token *begin, int end_index, \
					unsigned int nb, int error_i)
{
	int		index_last;
	t_token	*tmp;

	index_last = -1;
	tmp = begin;
	if (nb <= 0)
		return (index_last);
	index_last = find_last_heredoc(begin, end_index);
	while (tmp && tmp->index < end_index)
	{
		if (tmp->e_tk_type == TK_DLOWER && \
			((tmp->index < error_i && error_i > -2)
				|| error_i == -2))
		{
			tmp->parsed = true;
			tmp->next_token->parsed = true;
			if (tmp->index == index_last)
				heredoc_parsing_sigint(tmp, index_last);
		}
		tmp = tmp->next_token;
	}
	g_global.minishell->sa.sa_handler = &handler_sigint_main;
	sigaction(SIGINT, &g_global.minishell->sa, NULL);
	return (index_last);
}

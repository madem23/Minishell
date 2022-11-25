/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:00:52 by mdemma            #+#    #+#             */
/*   Updated: 2022/10/07 13:00:54 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h"

void	heredoc_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token '%s'\n", s);
	exit(EXIT_FAILURE);
}

void heredoc_parsing(t_token *begin, unsigned int end_index)
{
	char	*line;
	int		fd;
	char	*limiter;
	t_token	*tmp;

	tmp = begin;
	while (tmp && tmp->index < end_index)
	{
		if (tmp->type == TK_DLOWER)
		{
			if (tmp->next_token->redir_token == true)
				heredoc_syntax_error(tmp->next_token->value);
			limiter = tmp->next_token->value;
			break ;
		}
		tmp = tmp->next_token;
	}
	fd = open("tmp_heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 777);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strnstr(line, limiter, ft_strlen(limiter)) && line[ft_strlen(limiter)] == '\n')
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
}
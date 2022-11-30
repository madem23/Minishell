/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:04:33 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:04:37 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h"

void	heredoc_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token '%s'\n", s);
	exit(EXIT_FAILURE);
}

int	find_last_heredoc(t_token *first_token, int end_index)
{
	int index_last;
	t_token	*tmp;

	tmp = first_token;
	index_last = 0;
	while (tmp && tmp->index < end_index)
	{
		if (tmp->type == TK_DLOWER)
			index_last = tmp->index;
		tmp = tmp->next_token;
	}
	return (index_last);
}

int	heredoc_parsing(t_token *begin, int end_index, unsigned int nb)
{
	char	*line;
	int		fd;
	char	*limiter;
	int		index_last;
	t_token	*tmp;

	index_last = -1;
	tmp = begin;
	if (nb <= 0)
		return (index_last);
	index_last = find_last_heredoc(begin, end_index);
	while (tmp && tmp->index < end_index)
	{
		if (tmp->type == TK_DLOWER)
		{
			if (tmp->next_token->redir_token == true)
				heredoc_syntax_error(tmp->next_token->value);
			tmp->parsed = true;
			tmp->next_token->parsed = true;
			if (tmp->index == index_last)
			{
				limiter = tmp->next_token->value;
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
				break ;
			}
		}
		tmp = tmp->next_token;
	}
	return (index_last);
}

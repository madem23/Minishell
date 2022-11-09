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

void	heredoc_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token '%s'\n", s);
	exit(EXIT_FAILURE);
}

void heredoc_parsing(t_token *begin, size_t end_index)
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

/*
int	manage_heredoc(char **av, t_input *input)
{
	char	*str;
	int		i;

	input->heredoc = 0;
	i = 0;
	str = "here_doc\0";
	while (av[1][i] == str[i] && av[1][i])
		i++;
	if (av[1][i] == '\0' && str[i] == '\0')
	{
		heredoc_parsing(input);
		i = 3;
	}
	else
		i = 2;
	return (i);
}*/

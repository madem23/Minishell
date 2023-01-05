/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:54:22 by anloisea          #+#    #+#             */
/*   Updated: 2023/01/05 15:54:51 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_rest(char *s, int i)
{
	char	*rest;

	while (ft_isspace(s[--i]))
		;
	if (s[i] == '|')
	{
		error_syntax("|");
		return (0);
	}
	rest = readline("> ");
	while (rest && !ft_strcmp(rest, ""))
	{
		free(rest);
		rest = readline("> ");
	}
	if (!rest)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\nexit\n", 2);
		free(rest);
		exit(2);
	}
	return (rest);
}

int	check_finishing_pipe(char *s, t_minishell *minishell)
{
	int		i;
	char	*rest;
	char	*new;

	i = 0;
	while (s[i])
		i++;
	if (i > 0 && s[--i] == '|')
	{
		rest = get_rest(s, i);
		minishell->cmd_line = strcut_endl(minishell->cmd_line);
		new = ft_strjoin(minishell->cmd_line, rest);
		free(minishell->cmd_line);
		minishell->cmd_line = (char *) NULL;
		free(rest);
		minishell->cmd_line = new;
		if (minishell->cmd_line && *(minishell->cmd_line))
			add_history(minishell->cmd_line);
		return (1);
	}
	return (0);
}

int	check_beginning_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
	{
		error_syntax("|");
		return (0);
	}
	return (1);
}

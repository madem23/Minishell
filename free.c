/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:06:48 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/20 15:42:16 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees all elements of the executor.*/
void	free_end_executor(t_minishell *minishell, int **pipefd)
{
	int	nb;
	int	i;

	i = 0;
	nb = minishell->tree->nb_pipes + 1;
	if (pipefd)
	{
		while (nb-- > 0)
		{
			free(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
	free(minishell->p_id);
	free(g_global.u);
}

/* Frees all elements of the parser.*/
void	free_parser(t_parser *parser)
{
	t_token	*tmp;

	while (parser->first_token)
	{
		tmp = parser->first_token;
		parser->first_token = parser->first_token->next_token;
		free(tmp->value);
		free(tmp);
	}
	parser->lexer->cmd_line = NULL;
	free(parser->lexer->cmd_line);
	free(parser->lexer);
	free_tab((void **)parser->cmd_paths);
	free(parser);
}

/* Frees everything and quit when user send 'exit'.*/
void	free_exit_final(t_minishell *minishell)
{
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	free_tab((void **)minishell->envp);
	free(minishell);
	exit(EXIT_SUCCESS);
}

void	free_split_var(char **v)
{
	free(v[0]);
	free(v[1]);
	free(v);
}
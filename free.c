/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:06:48 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/02 11:11:09 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
}

void	free_branch(t_tree *branch)
{
	if (branch->exec_args)
		free_tab((void **)branch->exec_args);
	if (branch->exec_path)
		free(branch->exec_path);
	if (branch->exec_name)
		free(branch->exec_name);
	free(branch->infiles);
	free(branch->outfiles);
	free(branch->outfiles_append);
	free(branch);
}

void	free_tree(t_tree *treetop)
{
	t_tree	*tmp;

	while (treetop)
	{
		free_branch(treetop->branch);
		tmp = treetop;
		treetop = treetop->subtree;
		free(tmp);
	}
}

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
	free(parser->lexer);
	free_tab((void **)parser->cmd_paths);
	free(parser);
}

void	free_exit_final(t_minishell *minishell)
{
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	free(minishell);
	exit(EXIT_SUCCESS);
}

// void	free_tokens(t_parser *parser)
// {
// 	t_token *current_token;
// 	t_token	*tmp;

// 	current_token = parser->first_token;
// 	while (current_token->e_tk_type != TK_EOC)
// 	{
// 		tmp = current_token;
// 		if (tmp->value)
// 			free(tmp->value);
// 		current_token = tmp->next_token;
// 		free(tmp);
// 	}
// }

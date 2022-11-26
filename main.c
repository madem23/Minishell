/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/26 14:22:01 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line(t_minishell *minishell)
{
	if (minishell->cmd_line)
	{
		free (minishell->cmd_line);
		minishell->cmd_line = (char *)NULL;
    }
	minishell->cmd_line = readline(minishell->prompt);
	if (minishell->cmd_line && *(minishell->cmd_line))
		add_history(minishell->cmd_line);
}

t_minishell	*init_minishell(char *envp[])
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->envp = t_strcpy(envp);
	minishell->p_id = NULL;
	minishell->var_def = var_list_init(minishell->envp);
	minishell->prompt = get_prompt();
	minishell->cmd_line = NULL;
	get_line(minishell);
	minishell->lexer = NULL;
	minishell->parser = NULL;
	minishell->tree = NULL;
	return (minishell);
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;
	t_parser	*parser;

	(void)argc;
	(void)argv;
	minishell = init_minishell(envp);
	while (minishell->cmd_line)
	{
		if (minishell->cmd_line[0] != '\0')
		{
			minishell->lexer = lexer_init(minishell->cmd_line);
			parser = parser_init(minishell->lexer, minishell);
			minishell->parser = lexing_start(parser);
			minishell->tree = parser_start(minishell->parser, minishell);
			//DISPLAY LEXER:
			t_parser *tmp = minishell->parser;
			while (tmp->first_token)
			{
				printf("Created token = '%s', type: %d, index: %d.\n", tmp->first_token->value, tmp->first_token->type, tmp->first_token->index);
				printf("Parsed? %d\n", tmp->first_token->parsed);
				tmp->first_token = tmp->first_token->next_token;		
			}
			// // //DISPLAY TREE:
			//display_tree(minishell->tree);
			pipex(minishell);
			unlink("tmp_heredoc.txt");
		}
		minishell->prompt = get_prompt();
		get_line(minishell);
	}
	print_var(minishell);
	return (0);
}

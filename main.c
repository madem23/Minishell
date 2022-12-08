/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/12/02 16:07:46 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line(t_minishell *minishell)
{
	if (minishell->cmd_line)
	{
		free(minishell->cmd_line);
		minishell->cmd_line = (char *)NULL;
    }
	minishell->cmd_line = readline(minishell->prompt);
	free(minishell->prompt);
	if (minishell->cmd_line && *(minishell->cmd_line))
		add_history(minishell->cmd_line);
}

void	handler_sigint_main(int sig)
{
	(void)sig;

	if (global.sigint_heredoc == false)
	{
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	}
}

//rajouter les free ?
void	handler_sigint_child(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
}

//rajouter les free ?
void	handler_sigint_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit(130);
}

t_minishell	*init_minishell(char *envp[])
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->envp = NULL;
	minishell->p_id = NULL;
	minishell->var_def = var_list_init(envp);
	minishell->prompt = get_prompt();
	minishell->cmd_line = NULL;
	minishell->sa.sa_handler = &handler_sigint_main;
	minishell->sa.sa_flags = SA_RESTART;
	sigemptyset(&minishell->sa.sa_mask);
	sigaction(SIGINT, &minishell->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	get_line(minishell);
	minishell->lexer = NULL;
	minishell->parser = NULL;
	minishell->tree = NULL;
	return (minishell);
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell		*minishell;
	t_parser		*parser;
	
	
	(void)argc;
	(void)argv;
	global.sigint_heredoc = false;
	minishell = init_minishell(envp);
	global.minishell = minishell;
	while (minishell->cmd_line)
	{	
		update_envp(minishell);
		if (minishell->cmd_line[0])
		{
			global.u = malloc(sizeof(t_utils));
			minishell->lexer = lexer_init(minishell->cmd_line);
			parser = parser_init(minishell->lexer, minishell);
			minishell->parser = lexing_start(parser);
			minishell->tree = parser_start(minishell->parser, minishell);
			// //DISPLAY LEXER:
			// t_parser *tmp = minishell->parser;
			// while (tmp->first_token)
			// {
			// 	printf("Created token = '%s', type: %d, index: %d.\n", tmp->first_token->value, tmp->first_token->e_tk_type, tmp->first_token->index);
			// 	printf("Parsed? %d\n", tmp->first_token->parsed);
			// 	tmp->first_token = tmp->first_token->next_token;		
			// }
			// //DISPLAY TREE:
			// display_tree(minishell->tree);
			executor(minishell);
			unlink("tmp_heredoc.txt");
			unlink("empty_heredoc.txt");
		}
		minishell->prompt = get_prompt();
		get_line(minishell);
		if (minishell->cmd_line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
	return (0);
}
	
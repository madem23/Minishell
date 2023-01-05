/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2023/01/05 15:43:20 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line(t_minishell *minishell)
{
	if (minishell->cmd_line)
	{
		free(minishell->cmd_line);
		minishell->cmd_line = (char *) NULL;
	}
	minishell->cmd_line = readline(minishell->prompt);
	free(minishell->prompt);
	if (minishell->cmd_line && *(minishell->cmd_line))
		add_history(minishell->cmd_line);
}

t_minishell	*init_minishell(char *envp[])
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->envp = NULL;
	minishell->p_id = NULL;
	minishell->var_def = var_list_init(envp);
	minishell->prompt = get_prompt(minishell);
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

void	set_global_struct(t_minishell *minishell)
{
	g_global.sigint_heredoc = false;
	g_global.error_parsing = false;
	g_global.ambi_redir = false;
	g_global.new_cmdline = false;
	g_global.minishell = minishell;
}

void	parse_and_check_for_exec(t_minishell *minishell)
{
	t_parser	*parser;

	if (check_beginning_pipe(minishell->cmd_line))
	{
		g_global.u = malloc(sizeof(t_utils));
		minishell->lexer = lexer_init(minishell->cmd_line);
		parser = parser_init(minishell->lexer, minishell);
		minishell->parser = lexing_start(parser);
		minishell->tree = parser_start(minishell->parser, minishell);
	}
	if (g_global.error_parsing == false && \
		check_finishing_pipe(minishell->cmd_line, minishell))
	{	
		free_tree_and_parser(parser);
		g_global.new_cmdline = true;
	}
	else if (g_global.error_parsing == true)
	{
		g_global.error_parsing = false;
		free_tree_and_parser(parser);
	}
	else
		executor(minishell);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = init_minishell(envp);
	set_global_struct(minishell);
	while (minishell->cmd_line)
	{
		update_envp(minishell);
		if (minishell->cmd_line[0])
		{
			parse_and_check_for_exec(minishell);
			unlink("tmp_heredoc.txt");
			unlink("empty_heredoc.txt");
		}
		if (g_global.new_cmdline == true)
			g_global.new_cmdline = false;
		else
		{
			minishell->prompt = get_prompt(minishell);
			get_line(minishell);
		}
	}
	ft_putstr_fd("exit\n", 1);
	return (0);
}

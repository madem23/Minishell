/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpolpa <elpolpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/12/22 10:31:32 by elpolpa          ###   ########.fr       */
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
	if (g_global.sigint_heredoc == false)
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

//only ctrl D to quit readline here
//LEAKS: rajouter les frees du exit
int	check_finishing_pipe(char *s, t_minishell *minishell)
{
	int i;
	char *rest;
	char *new;

	i = 0;
	while (s[i])
		i++;
	if (i > 0 && s[--i] == '|')
	{
		while (ft_isspace(s[--i]));
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
		minishell->cmd_line = strcut_endl(minishell->cmd_line);
		new = ft_strjoin(minishell->cmd_line, rest);
		free(minishell->cmd_line);
		minishell->cmd_line = (char *)NULL;
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
	int i;

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

int main(int argc, char *argv[], char *envp[])
{
	t_minishell		*minishell;
	t_parser		*parser;
	
	
	(void)argc;
	(void)argv;
	g_global.sigint_heredoc = false;
	g_global.error_parsing = false;
	g_global.ambi_redir = false;
	g_global.new_cmdline = false;
	minishell = init_minishell(envp);
	g_global.minishell = minishell;
	while (minishell->cmd_line)
	{
		update_envp(minishell);
		if (minishell->cmd_line[0])
		{
			if (check_beginning_pipe(minishell->cmd_line))
			{
				
				g_global.u = malloc(sizeof(t_utils));
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
			}
			if (g_global.error_parsing == false && check_finishing_pipe(minishell->cmd_line, minishell))
			{	
				free_tree(parser->treetop);
				free_parser(parser);
				free(g_global.u);
				g_global.new_cmdline = true;
			}
			else if (g_global.error_parsing == true)
			{
				g_global.error_parsing = false;
				free_tree(parser->treetop);
				free_parser(parser);
				free(g_global.u);
			}
			else
				executor(minishell);
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
		if (minishell->cmd_line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
	return (0);
}
	
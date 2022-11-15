/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/15 13:48:06 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char *s,	t_token **tab, int i)
{
	if (!tab[i])
	{
		printf("%s NULL\n", s);
		return ;
	}
	printf("%s", s);
	while (tab[i])
		printf("%s, ", tab[i++]->value);
	printf("\n");
}

void	print_tabchar(char *s,	char **tab, int i)
{
	if (!tab[i])
	{
		printf("%s NULL\n", s);
		return ;
	}
	printf("%s", s);
	while (tab[i])
		printf("%s, ", tab[i++]);
	printf("\n");
}

void	display_tree(t_tree *top)
{
	t_tree *tmp1 = top;
	int	i = 1;

	while (tmp1)
	{
		printf("BRANCHE %d :\n", i);
		printf("	CMD = '%s'\n", tmp1->branch->exec_name);
	print_tabchar("	CMD args/options = ", tmp1->branch->exec_args, 0);
		print_tab("	Infiles = ", tmp1->branch->infiles, 0);
		print_tab("	Outfiles = ", tmp1->branch->outfiles, 0);
		print_tab("	Outfiles append-mode = ", tmp1-> branch->outfiles_append, 0);
		print_tab("	Diamonds = ", tmp1-> branch->diamonds, 0);
		tmp1 = tmp1->subtree;
		i++;
	}
}

void	print_var(t_minishell *minishell)
{
	t_var *tmp;

	tmp = minishell->var_def;
	while (tmp)
	{
		printf("Var_def enregistre: '%s' -> '%s'.\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

t_minishell	*init_minishell(char *envp[])
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->envp = envp;
	minishell->var_def = NULL;
	minishell->prompt = get_prompt();
	minishell->cmd_line = readline(minishell->prompt);
	minishell->lexer = NULL;
	minishell->parser = NULL;
	minishell->tree = NULL;
	return (minishell);
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = init_minishell(envp);
	while (minishell->cmd_line)
	{
		
		if (!ft_strncmp(minishell->cmd_line, "exit", 4))
			exit(0);
		if (minishell->cmd_line[0] != '\0')
		{
			minishell->lexer = lexer_init(minishell->cmd_line);
			minishell->parser = parser_init(minishell->lexer, envp);
			minishell->tree = parser_start(minishell->parser, minishell);
			// //DISPLAY LEXER:
			// t_parser *tmp = minishell->parser;
			// while (tmp->first_token)
			// {
			// 	printf("Created token = '%s', type: %d, index: %d.\n", tmp->first_token->value, tmp->first_token->type, tmp->first_token->index);
			// 	printf("Parsed? %d\n", tmp->first_token->parsed);
			// 	tmp->first_token = tmp->first_token->next_token;		
			// }
			// //DISPLAY TREE:
			// display_tree(minishell->tree);
		}
		pipex(minishell->tree);
		free(minishell->cmd_line);
		unlink("tmp_heredoc.txt");
		minishell->cmd_line = readline(minishell->prompt);
	}
	return (0);
}
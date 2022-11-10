/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/09 18:03:35 by anloisea         ###   ########.fr       */
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
	print_tabchar("	CMD args/options = ", tmp1->branch->exec_args, 1);
		print_tab("	Infiles = ", tmp1->branch->infiles, 0);
		print_tab("	Outfiles = ", tmp1->branch->outfiles, 0);
		print_tab("	Outfiles append-mode = ", tmp1-> branch->outfiles_append, 0);
		print_tab("	Diamonds = ", tmp1-> branch->diamonds, 0);
		tmp1 = tmp1->subtree;
		i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_parser	*parser;
	t_tree		*top;
	char		*cmd_line;

	(void)argc;
	(void)argv;
	cmd_line = "coucou";
	while (cmd_line)
	{
		cmd_line = readline("Enter a command: ");
		if (cmd_line[0] != '\0')
		{
			parser = parser_init(lexer_init(cmd_line), envp);
			top = parser_start(parser);

			//DISPLAY LEXER:
			t_parser *tmp = parser;
			while (tmp->first_token)
			{
				printf("Created token = '%s', type: %d, index: %ld.\n", tmp->first_token->value, tmp->first_token->type, tmp->first_token->index);
				printf("Parsed? %d\n", tmp->first_token->parsed);
				tmp->first_token = tmp->first_token->next_token;		
			}
			//DISPLAY TREE:
			display_tree(top);
			unlink("tmp_heredoc.txt");
		}
		pipex(top);
	}
	return (0);
}
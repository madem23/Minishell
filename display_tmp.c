/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/15 16:12:35 by antoine          ###   ########.fr       */
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
		printf(" piped input = %d\n", tmp1->branch->piped_input);
		printf(" piped output = %d\n", tmp1->branch->piped_output);
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
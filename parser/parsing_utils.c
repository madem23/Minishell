#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

t_token	**filling_redir_files_tab(t_tree *branch, int size, size_t type)
{
	t_token	*tmp;
	t_token	**tab;
	int		i;
	
	i = 0;
	tmp = branch->first_token;
	tab = malloc(sizeof(t_token *) * size);
	if (!tab)
	{
		printf("Error in allocating redir tab.\n");
		exit(EXIT_FAILURE);
	}
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->type == type)
		{
			tmp->parsed = true;
			tmp = tmp->next_token;
			tmp->parsed = true;
			tab[i++] = tmp;
		}
		tmp = tmp->next_token;
	}
	tab[i] = NULL;
	return (tab);
}

void	parsing_redir(t_tree *branch)
{
	t_token	*tmp;

	tmp = branch->first_token;
	branch->nb_infiles = 0;
	branch->nb_outfiles = 0;
	branch->nb_outfiles_append = 0;
	branch->nb_diamonds = 0;
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->type == TK_LOWER)
			branch->nb_infiles++;
		else if (tmp->type == TK_GREATER)
			branch->nb_outfiles++;
		else if (tmp->type == TK_DGREATER)
			branch->nb_outfiles_append++;
		else if (tmp->type == TK_LOWER_GREATER)
			branch->nb_diamonds++;
		tmp = tmp->next_token;
	}
	branch->infiles = filling_redir_files_tab(branch, branch->nb_infiles + 1, TK_LOWER);
	branch->outfiles = filling_redir_files_tab(branch, branch->nb_outfiles + 1, TK_GREATER);
	branch->outfiles_append = filling_redir_files_tab(branch, branch->nb_outfiles_append + 1, TK_DGREATER);
	branch->diamonds = filling_redir_files_tab(branch, branch->nb_diamonds + 1, TK_LOWER_GREATER);
}

int	count_unparsed_word(t_tree *branch)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = branch->first_token;
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->type == TK_WORD && tmp->parsed == false)
			count++;
		tmp = tmp->next_token;
	}
	return (count);
}

//tab[0] = cmd, rest is args/options
void	parsing_cmd(t_tree *branch)
{
	t_token	*tmp;
	int		i;
	int 	size;

	i = 0;
	tmp = branch->first_token;
	size = count_unparsed_word(branch);
	branch->exec_args = malloc(sizeof(char *) * (size + 1));
	if (!branch->exec_args)
		error(2, "Error in allocating cmd tab.\n");
	while (tmp && tmp->index <= branch->end_index)
	{
		if ((tmp->type == TK_WORD || tmp->type == TK_DOLLAR)
			 && (tmp->parsed == false && i == 0))
		{
			tmp->parsed = true;
			branch->exec_args[i++] = ft_strdup(tmp->value);
		}	 
		if ((tmp->type == TK_WORD || tmp->type == TK_EQUAL || tmp->type == TK_DOLLAR)
			 && (tmp->parsed == false && i > 0))
		{
			tmp->parsed = true;
			branch->exec_args[i++] = ft_strdup(tmp->value);
		}
		tmp = tmp->next_token;
	}
	branch->exec_args[i] = NULL;
}
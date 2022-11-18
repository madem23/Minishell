#include "parser.h"

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

char **separate_name_value(char *var, char c)
{
	int		begin;
	int 	end;
	char	**result;

	begin = 0;
	end = 0;
	result = malloc(3 * sizeof(char *));
	while (var[end] && var[end] != c)
		end++;
	result[0] = ft_substr(var, begin, end);
	begin = end + 1;
	while (var[end])
		end++;
	result[1] = ft_substr(var, begin, end - begin);
	result[2] = NULL;
	return (result);
}

t_var	*var_list_init(char **envp)
{
	t_var	*list;
	int		i;
	char	**trim;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		trim = separate_name_value(envp[i], '=');
		var_add_back(&list, variable_init(trim[0], trim[1]));
		free(trim);
		i++;
	}
	// while (list)
	// {
	// 	printf("var = %s\tvalue = %s\tenv = %d\n", list->name, list->value, list->env);
	// 	list = list->next;
	// }
	return (list);
}

void	var_add_back(t_var **var, t_var *new)
{
	t_var	*tmp;

	tmp = *var;
	if (!*var)
	{
		*var = new;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_var	*variable_init(char	*name, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->name = name;
	var->value = value;
	var->next = NULL;
	return (var);
}

//Checks if declared var already exists in env or in local list, if yes, modifies it
//nb: j = location of '=' in token_value
int	modify_existing_var(t_tree *branch, char *token_value, int j)
{
	int	i;
	t_var	*tmp;

	i = 0;
	while (branch->treetop->envp[i])
	{
		if (!ft_strncmp(branch->treetop->envp[i], token_value, j))
		{
			free(branch->treetop->envp[i]);
			branch->treetop->envp[i] = ft_strdup(token_value);
			return (1);
		}
		i++;
	}
	tmp = branch->minishell->var_def;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, token_value, j))
		{
			free(tmp->value);
			tmp->value = ft_strdup(token_value + ++j);
			printf("new var '%s' value = %s\n", tmp->name, tmp->value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	parsing_var_def(t_tree *branch)
{	
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = branch->first_token;
	if (!branch->exec_name && branch->piped_input == false && branch->piped_output == false)
	{
		while (tmp && tmp->index <= branch->end_index)
		{
			if (tmp->type == TK_EQUAL)
			{
				while (tmp->value[i] && tmp->value[i] != '=')
					i++;
				if (modify_existing_var(branch, tmp->value, i))
				{
					printf("TEST RETURN ENV\n");
					return ;
				}
				else
				{
					var_add_back(&branch->minishell->var_def,
						variable_init(ft_substr(tmp->value, 0, i), ft_strdup(tmp->value + i + 1)));
				}
				i = 0;
			}
			tmp = tmp->next_token;
		}
	}
}
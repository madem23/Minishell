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
		free(trim[0]);
		free(trim[1]);
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

int	check_var_envp(char **envp, char *var_name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, ft_strlen(var_name)))
			return (1);
		i++;
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
				if (check_var_envp(branch->treetop->envp, tmp->value))
				{
					printf("TEST RETURN ENV\n");
					return ;
				}
				if (!branch->minishell->var_def)
					branch->minishell->var_def = variable_init(ft_substr(tmp->value, 0, i), ft_strdup(tmp->value + i + 1));
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
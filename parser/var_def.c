#include "parser.h"

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_def.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:01:37 by antoine           #+#    #+#             */
/*   Updated: 2022/11/22 16:44:49 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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

t_var	*variable_init(char	*name, char *value, bool env)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->name = name;
	var->value = value;
	var->next = NULL;
	var->env = env;
	return (var);
}

t_var	*var_list_init(char **envp)
{
	t_var	*list;
	int		i;
	char	**trim;
	t_var	*tmp;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		trim = separate_name_value(envp[i], '=');
		var_add_back(&list, variable_init(trim[0], trim[1], false));
		free(trim);
		i++;
	}
	tmp = list;
	while (tmp)
	{
		tmp->env = true;
		tmp = tmp->next;
	}
	return (list);
}

//Checks if declared var already exists in env or in local list, if yes, modifies it
//nb: j = location of '=' in token_value
int	modify_existing_var(t_tree *branch, char *token_value, int j)
{
	int	i;
	t_var	*tmp;

	i = 0;
	tmp = branch->minishell->var_def;
	while (branch->treetop->envp[i])
	{
		if (!ft_strncmp(branch->treetop->envp[i], token_value, j))
		{
			free(branch->treetop->envp[i]);
			branch->treetop->envp[i] = ft_strdup(token_value);
			while (tmp)
			{
				if (!ft_strncmp(tmp->name, token_value, j))
				{
					free(tmp->value);
					tmp->value = ft_strdup(token_value + ++j);
				}
				tmp = tmp->next;
			}
			return (2);
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

int	modify_existing_string_var(t_tree *branch, char *var_name, char *var_value)
{
	int	i;
	t_var	*tmp;

	i = 0;
	tmp = branch->minishell->var_def;
	while (branch->treetop->envp[i])
	{
		if (!ft_strncmp(branch->treetop->envp[i], var_name, ft_strlen(var_name)))
		{
			if (var_value)
			{
				free(branch->treetop->envp[i]);
				branch->treetop->envp[i] = ft_strjoin(ft_strjoin(var_name, "="), var_value);
			}
			while (tmp)
			{
				if (!ft_strcmp(tmp->name, var_name))
				{
					if(var_value)
					{
						free(tmp->value);
						tmp->value = ft_strdup(var_value);
					}
				}
				tmp = tmp->next;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing_var_def(t_tree *branch)
{	
	t_token	*tmp;
	char	**var_def;

	tmp = branch->first_token;
	var_def = ft_split(tmp->value, '=');
	if (!branch->exec_name && branch->piped_input == false && branch->piped_output == false)
	{
		while (tmp && tmp->index <= branch->end_index)
		{
			if (tmp->type == TK_EQUAL && tmp->next_token->type != TK_DQUOTE)
			{
				if (modify_existing_string_var(branch, var_def[0], var_def[1]))
				{
					free_tab(var_def);
					return (1);
				}
				else
					var_add_back(&branch->minishell->var_def,
						variable_init(ft_strdup(var_def[0]), ft_strdup(var_def[1]), false));
			}
			else if (tmp->type == TK_EQUAL && tmp->next_token->type == TK_DQUOTE)
			{
				if (modify_existing_string_var(branch, var_def[0], tmp->next_token->value))
				{
					free_tab(var_def);
					return (1);
				}
				else
					var_add_back(&branch->minishell->var_def,
						variable_init(ft_strdup(var_def[0]), ft_strdup(tmp->next_token->value), false));
			}
			tmp = tmp->next_token;
		}
	}
	free_tab(var_def);
	return (0);
}

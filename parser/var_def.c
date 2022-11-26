/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_def.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:01:37 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 20:16:48 by antoine          ###   ########.fr       */
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

	i = 0;
	list = NULL;
	var_add_back(&list, variable_init(ft_strdup("?"), ft_itoa(0), false));
	while (envp[i])
	{
		trim = separate_name_value(envp[i], '=');
		var_add_back(&list, variable_init(trim[0], trim[1], true));
		free(trim);
		i++;
	}
	change_variable_value(list, "SHELL", "./minishell");
	return (list);
}

// int	modify_existing_string_var(t_tree *branch, char *var_name, char *var_value)
// {
// 	int	i;
// 	t_var	*tmp;

// 	i = 0;
// 	tmp = branch->minishell->var_def;
// 	while (branch->treetop->envp[i])
// 	{
// 		if (!ft_strncmp(branch->treetop->envp[i], var_name, ft_strlen(var_name)))
// 		{
// 			if (var_value)
// 			{
// 				free(branch->treetop->envp[i]);
// 				branch->treetop->envp[i] = ft_strjoin(ft_strjoin(var_name, "="), var_value);
// 			}
// 			while (tmp)
// 			{
// 				if (!ft_strcmp(tmp->name, var_name))
// 				{
// 					if(var_value)
// 					{
// 						free(tmp->value);
// 						tmp->value = ft_strdup(var_value);
// 					}
// 				}
// 				tmp = tmp->next;
// 			}
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	parsing_var_def(t_tree *branch)
{	
	t_token	*tmp;
	char	**var_def;

	tmp = branch->first_token;
	if (!branch->exec_name && branch->piped_input == false && branch->piped_output == false)
	{
		while (tmp && tmp->index <= branch->end_index)
		{
			if (tmp->type == TK_EQUAL)
			{
				var_def = ft_split(tmp->value, '=');
				var_def[1] = parsing_quotes_dollar(var_def[1], branch->minishell, creating_word_parsing_tree(var_def[1], branch->minishell)); 
				if (change_variable_value(branch->minishell->var_def, var_def[0], var_def[1]))
					return (1);
				else
					var_add_back(&branch->minishell->var_def,
						variable_init(ft_strdup(var_def[0]), ft_strdup(var_def[1]), false));
			}
			tmp = tmp->next_token;
		}
	}
	return (0);
}

int	change_variable_value(t_var *list, char *name, char *value)
{
	t_var	*tmp;
	
	tmp = list;
	while (tmp && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		return (1);
	}
	return (0);
}

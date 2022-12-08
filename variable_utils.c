/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:02:07 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/08 17:45:11 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the value corresponding the variable name received. */
char	*get_var_value(t_var *var_list, char *name)
{
	t_var	*tmp;
	char	*value;

	tmp = var_list;
	value = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			value = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (value);
}

char	**separate_name_value(char *var, char c)
{
	int		begin;
	int		end;
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

t_var	*var_init(char	*name, char *value, bool env)
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
	char	*oldpwd;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		trim = separate_name_value(envp[i], '=');
		var_add_back(&list, var_init(trim[0], trim[1], true));
		free(trim);
		i++;
	}
	oldpwd = get_var_value(list, "OLDPWD");
	if (!oldpwd)
		var_add_back(&list, var_init(ft_strdup("OLDPWD"),
				getcwd(NULL, 0), true));
	free(oldpwd);
	change_var_value(list, "SHELL", "./minishell");
	return (list);
}

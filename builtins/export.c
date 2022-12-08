/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:25:12 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 17:31:13 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parser/parser.h"
#include "../expander/expander.h"

int	check_for_invalid_identifier(char *exec_arg)
{
	if (ft_strchrset(exec_arg, "\"\'!@#^%&*()- +[]{}:;.,?") != -1
		|| ft_isdigit(exec_arg[0]))
	{
		ft_putstr_fd("minishell: export: \'", 2);
		ft_putstr_fd(exec_arg, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

void	create_var_entry_in_env(char *var_name, t_minishell *minishell)
{
	t_var	*tmp;

	tmp = minishell->var_def;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->name) == 0 && tmp->env == false)
			tmp->env = true;
		tmp = tmp->next;
	}
}

int	display_declare_x(t_var *var_list)
{
	while (var_list)
	{
		if (var_list->env == true)
			printf("declare -x %s=%s\n", var_list->name, var_list->value);
		var_list = var_list->next;
	}
	return (0);
}

int	export(t_tree *branch, t_minishell *minishell)
{
	int		i;
	char	**var_def;

	if (tab_len(branch->exec_args) == 1)
		return (display_declare_x(minishell->var_def));
	i = 0;
	while (branch->exec_args[++i])
	{
		if (check_for_invalid_identifier(branch->exec_args[i]))
			return (1);
		var_def = ft_split(branch->exec_args[i], '=');
		if (var_def[1])
			var_def[1] = expander_convert(branch->minishell,
					creating_expander_tree(var_def[1]));
		if (locate_char(branch->exec_args[i], '=') >= 0)
		{
			if (var_def && !change_var_value(minishell->var_def,
					var_def[0], var_def[1]))
				var_add_back(&branch->minishell->var_def,
					var_init(ft_strdup(var_def[0]),
						ft_strdup(var_def[1]), true));
		}
	}
	return (0);
}

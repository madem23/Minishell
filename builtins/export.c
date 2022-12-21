/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:25:12 by antoine           #+#    #+#             */
/*   Updated: 2022/12/21 17:15:52 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parser/parser.h"
#include "../expander/expander.h"
#include "../lexer/token.h"

int	is_exportable(char *value)
{
	int	i;

	i = 0;
	if (value[0] && !ft_isalpha(value[0]) && value[0] != '_')
		return (0);
	while (ft_isaccepted_var_name(value[i]) && value[i] != '=')
		i++;
	if (i == 0)
		return (0);
	if (i > 0 && !value[i])
		return (1);
	if (!value[++i] || ft_isaccepted(value[i]) || ft_isspace(value[i]))
		return (1);
	else
		return (0);
}

int	check_for_invalid_identifier(char *exec_arg)
{
	if (!is_exportable(exec_arg) || ft_isdigit(exec_arg[0])
		|| !ft_strcmp(exec_arg, ""))
	{
		ft_putstr_fd("minishell: export: \'", 2);
		ft_putstr_fd(exec_arg, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
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

void	declare_variable(t_tree *branch, t_minishell *minishell, int i)
{
	char	**var_def;

	var_def = ft_split(branch->exec_args[i], '=');
	if (var_def[1])
		var_def[1] = expander_convert(branch->minishell,
				creating_expander_tree(var_def[1]));
	if (locate_char(branch->exec_args[i], '=') >= 0)
	{
		if (!var_def[1])
			var_def[1] = ft_strdup("");
		if (var_def && !change_var_value(minishell->var_def,
				var_def[0], var_def[1]))
			var_add_back(&branch->minishell->var_def,
				var_init(ft_strdup(var_def[0]),
					ft_strdup(var_def[1]), true));
	}
	else
		create_var_entry_in_env(var_def[0], minishell);
	free_split_var(var_def);
}

int	export(t_tree *branch, t_minishell *minishell)
{
	int		i;
	int		exit;

	exit = 0;
	if (tab_len(branch->exec_args) == 1)
		return (display_declare_x(minishell->var_def));
	i = 0;
	while (branch->exec_args[++i])
	{
		if (!check_for_invalid_identifier(branch->exec_args[i]))
			declare_variable(branch, minishell, i);
		else
			exit = 1;
	}
	return (exit);
}

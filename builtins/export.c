/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:25:12 by antoine           #+#    #+#             */
/*   Updated: 2022/11/17 14:23:31 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export(char **args, char **envp, t_minishell *minishell)
{
	int		i;
	t_var	*tmp;
	char	*new_value;

	new_value = NULL;
	if (tab_len(args) == 1)
	{
		i = 0;
		while (envp[i])
		{
			printf("declare -x ");
			printf("%s\n", envp[i]);
			i++;
		}
	}
	tmp = minishell->var_def;
	while (tmp)
	{
		if (ft_strcmp(args[1], tmp->name) == 0)
			new_value = ft_strjoin(ft_strjoin(tmp->name, "="), tmp->value);
		tmp = tmp->next;
	}
	if (new_value)
		envp = add_str_to_tab(envp, new_value);
	free(new_value);
} 
	
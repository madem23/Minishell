/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:33:01 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 17:50:09 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// char	**rmv_str_from_tab(char **envp, char *str)
// {
// 	int		i;
// 	char	**new_env;

// 	i = 0;
// 	new_env = malloc(tab_len(envp) * sizeof(char *));
// 	while (envp[i] && ft_strncmp(envp[i], str, ft_strlen(str)))
// 	{
// 		new_env[i] = ft_strdup(envp[i]);
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp[i]);
// 	i++;
// 	while (envp[i])
// 	{
// 		new_env[i - 1] = ft_strdup(envp[i]);
// 		free(envp[i]);
// 		i++;
// 	}
// 	new_env[i - 1] = NULL;
// 	free(envp);
// 	return (new_env);
// }

void	rmv_var_from_list(t_var	**list, t_var *var)
{
	t_var	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->next == var)
		{
			free(var->name);
			free(var->value);
			tmp->next = var->next;
			free(var);
		}
		tmp = tmp->next;
	}
}

int unset(char **args, t_minishell *minishell)
{
	int		i;
	t_var	*tmp;

	i = 1;
	while (args[i])
	{
		tmp = minishell->var_def;
		while (tmp)
		{
			if (!ft_strcmp(args[i], tmp->name))
				rmv_var_from_list(&minishell->var_def, tmp);
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

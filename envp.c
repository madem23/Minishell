/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:00:19 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 11:10:11 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* updates envp from var_list (tab of strings). */

int	get_env_var_len(t_var *var_list)
{
	int	len;

	len = 0;
	while (var_list)
	{
		if (var_list->env == true)
			len++;
		var_list = var_list->next;
	}
	return (len);
}

void	update_envp(t_minishell *minishell)
{
	int		len;
	t_var	*tmp;
	int		i;
	char	*join_equal;

	if (minishell->envp)
		free_tab((void **)minishell->envp);
	tmp = minishell->var_def;
	len = get_env_var_len(minishell->var_def);
	minishell->envp = malloc((len + 1) * sizeof(char *));
	i = 0;
	tmp = minishell->var_def;
	while (tmp)
	{
		if (tmp->env == true)
		{
			join_equal = ft_strjoin(tmp->name, "=");
			minishell->envp[i] = ft_strjoin(join_equal, tmp->value);
			free(join_equal);
			i++;
		}
		tmp = tmp->next;
	}
	minishell->envp[i] = NULL;
}

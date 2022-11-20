/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:25:12 by antoine           #+#    #+#             */
/*   Updated: 2022/11/18 12:05:12 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parser/parser.h"

//need to clean join

void	is_var_def(char	**args, t_tree* branch)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			parsing_var_def(branch);
		i++;
	}
}

//returns the index of the first occurence of a char
int	locate_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-1);
	else
		return (i);	
}

void	export(t_tree *branch, t_minishell *minishell)
{
	int		i;
	t_var	*tmp;
	char	*new_value;
	int		modif_status;
	int		i_equal;

	modif_status = 0;
	if (tab_len(branch->exec_args) == 1)
	{
		i = 0;
		while (minishell->envp[i])
		{
			printf("declare -x ");
			printf("%s\n", minishell->envp[i]);
			i++;
		}
		return ;
	}
		//si 1, deja dans list, doit etre mis dans env:
	is_var_def(branch->exec_args, branch);
	i = 1;
	while (branch->exec_args[i])
	{
		i_equal = locate_char(branch->exec_args[i], '=');
		if (i_equal == -1)
			i_equal = ft_strlen(branch->exec_args[i]);
		modif_status = modify_existing_var(branch, branch->exec_args[i], i_equal);
		if (modif_status == 0) //existe encore nulle part, doit etre en plus rajoute dans list
		{
			var_add_back(&branch->minishell->var_def,
				variable_init(ft_substr(branch->exec_args[i], 0, i_equal), ft_strdup(branch->exec_args[i] + i_equal + 1), false));
		}
		tmp = minishell->var_def;
		new_value = NULL;
		
		while (tmp)
		{
			if (ft_strncmp(branch->exec_args[i], tmp->name, i_equal) == 0 && tmp->env == false)
			{
				tmp->env = true;
				new_value = ft_strjoin(ft_strjoin(tmp->name, "="), tmp->value);
			}
			tmp = tmp->next;
		}
		if (new_value)
			minishell->envp = add_str_to_tab(minishell->envp, new_value);
		free(new_value);
		i++;
	}
} 
	
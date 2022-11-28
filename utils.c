/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:19 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 20:09:41 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns the index of the first occurence of a char
int	locate_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-1);
	else
		return (i);	
}

//locate the first occurence of any char of the charset in *s
int	ft_strchrset(const char *s, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (charset[j])
		{
			if (s[i] == charset[j])
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}

int	ft_isaccepted_var_name(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '_' || c == '?')
		return (1);
	else
		return (0);
}

int	ft_isaccepted(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c >= 33 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 61)
		return (1);
	else if (c == 63)
		return (1);
	else if (c == 123 || c == 125)
		return (1);
	else if (c >= 91 && c <= 95)
		return (1);
	else if (c == 126)
		return (1);
	else
		return (0);
}

char	*get_prompt()
{
	char	*prompt;
	char	*current_dir;
	char	*color;
	char	*tmp;

	current_dir = getcwd(NULL, 0);
	color = ft_strjoin("\033[0;34m", current_dir);
	free(current_dir);
	prompt = ft_strjoin("\033[0;32mminishell: ", color);
	free(color);
	tmp = prompt;
	prompt = ft_strjoin(tmp, "$ \033[0m");
	free(tmp);
	return (prompt);
}

char	**t_strcpy(char **t_str)
{
	char	**copy;
	int		i;

	copy = malloc((tab_len(t_str) + 1) * sizeof(char *));
	i = 0;
	while (t_str[i])
	{
		copy[i] = ft_strdup(t_str[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**add_str_to_tab(char **tab, const char *str)
{
	char	**result;
	int		i;
	
	i = 0;
	result = malloc((tab_len(tab) + 2) * sizeof(char *));
	while (tab[i])
	{
		result[i] = ft_strdup(tab[i]);
		free(tab[i]);
		i++;
	}
	result[i] = ft_strdup(str);
	result[i + 1] = NULL;
	free(tab);
	return (result);
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
	len = 0;
	while (tmp)
	{
		if (tmp->env == true)
			len++;
		tmp = tmp->next;
	}
	minishell->envp = malloc((len + 1) * sizeof(char*));
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

char	*get_variable_value(t_var *var_list, char *name)
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

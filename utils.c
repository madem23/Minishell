/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:19 by antoine           #+#    #+#             */
/*   Updated: 2022/11/17 14:05:10 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isaccepted_var_name(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

int	ft_isaccepted(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c >= 33 && c <= 45)
		return (1);
	else if (c >= 46 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 61)
		return (1);
	else if (c == 123 || c == 125)
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
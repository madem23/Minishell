/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:19 by antoine           #+#    #+#             */
/*   Updated: 2022/12/15 17:00:56 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 1 if char is accepted in a variable name. */
int	ft_isaccepted_var_name(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

/* Returns 1 if char c is accepted as part of a word. */
int	ft_isaccepted(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c >= 33 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 59)
		return (1);
	else if (c == 61 || c == 63)
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

/* Create string to use as prompt by readline. */
char	*get_prompt(t_minishell * minishell)
{
	char	*prompt;
	char	*current_dir;
	char	*color;
	char	*tmp;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		current_dir = get_var_value(minishell->var_def, "PWD");
	color = ft_strjoin("\033[0;34m", current_dir);
	free(current_dir);
	prompt = ft_strjoin("\033[0;32mminishell: ", color);
	free(color);
	tmp = prompt;
	prompt = ft_strjoin(tmp, "$ \033[0m");
	free(tmp);
	return (prompt);
}

/* Adds a string at the end of a tab of strings. */
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

/* Malloc with security for strings.*/
char	*malloc_string(int size)
{
	char	*str;

	str = malloc((size) * sizeof(char));
	if (str == NULL)
		error(1, "failed to allocate string\n");
	return (str);
}

void	check_malloc(void *p)
{
	if (!p)
	{
		printf("Error in allocating pointer.\n");
		exit(EXIT_FAILURE);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:19 by antoine           #+#    #+#             */
/*   Updated: 2022/12/22 10:36:11 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create string to use as prompt by readline. */
char	*get_prompt(t_minishell *minishell)
{
	char	*prompt;
	char	*current_dir;
	char	*color;
	char	*tmp;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		current_dir = get_var_value(minishell->var_def, "PWD");
	if (!current_dir)
		current_dir = ft_strdup(".");
	color = ft_strjoin("\033[0;34m", current_dir);
	free(current_dir);
	prompt = ft_strjoin("\033[0;32mminishell:", color);
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

char	**ft_trim_at_char(char *str, char c)
{
	char	**trim;
	int		i;
	int		j;

	if (ft_strchr(str, c))
		trim = malloc(sizeof(char *) * 3);
	else
		trim = malloc(sizeof(char *) * 2);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	trim[0] = ft_substr(str, 0, i);
	if (!str[i] || (str[i] == '=' && !str[i + 1]))
		trim[1] = NULL;
	else
	{
		i++;
		j = i;
		while (str[i])
			i++;
		trim[1] = ft_substr(str, j, i - j);
		trim[2] = NULL;
	}
	return (trim);
}

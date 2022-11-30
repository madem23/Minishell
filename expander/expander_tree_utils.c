/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tree_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:03:14 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:03:16 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../parser/parser.h"
#include "../minishell.h"
#include "../libft/libft.h"

char	*get_var(unsigned int *i, char *value)
{
	unsigned int	save;

	save = *i;
	(*i)++;
	if (value[*i] && value[*i] >= '0' && value[*i] <= '9')
	{
		*i += 1;
		return (ft_substr(value, save, 2));
	}
	else if (value[*i] && !ft_isaccepted_var_name(value[*i]))
	{
		while (value[*i] && value[*i] != '$' && *i < (ft_strlen(value) - 1))
			(*i)++;
		return (ft_substr(value, save, *i - save));
	}
	else
	{
		while (value[*i] && ft_isaccepted_var_name(value[*i]))
			(*i)++;
		return (ft_substr(value, save, *i - save));
	}
}

//for opening token only
char	*get_word(unsigned int *i, char *value)
{
	char	*s;
	int		j;
	unsigned int		save;

	j = 0;
	save = *i;
	while (value[*i] && value[*i] != '$' && *i < (ft_strlen(value) - 1))
		(*i)++;
	s = malloc(sizeof(char) * (*i - save + 1));
	while (value[save] && save < *i)
		s[j++] = value[save++];
	s[j] = '\0';
	return (s);
}

char	*get_prev_word(unsigned int last_end, unsigned int *i, char *value)
{
	char	*s;
	int		j;
	int		verif;

	verif = 0;
	j = 0;	
	if (*i - last_end <= 1)
	{
		verif++;
		(*i)++;
	}
	if (last_end != 0)
		last_end++;
	s = malloc(sizeof(char) * (*i - last_end + 1));
	while (value[last_end] && last_end <= *i)
	{
		s[j++] = value[last_end];
		last_end++;
	}
	if (verif == 1)
		(*i)--;
	s[j] = '\0';
	return (s);
}

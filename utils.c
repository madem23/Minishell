/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:19 by antoine           #+#    #+#             */
/*   Updated: 2022/11/14 16:47:50 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = prompt;
	prompt = ft_strjoin(tmp, "$ \033[0m");
	free(tmp);
	return (prompt);
}
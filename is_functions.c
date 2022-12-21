/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:11:41 by antoine           #+#    #+#             */
/*   Updated: 2022/12/21 13:11:57 by antoine          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:19 by antoine           #+#    #+#             */
/*   Updated: 2022/11/09 18:08:16 by anloisea         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:37:09 by antoine           #+#    #+#             */
/*   Updated: 2022/12/08 17:37:14 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locates the first occurence of any char of the charset in *s.
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrnstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:02:56 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/25 13:56:04 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(haystack) - 1;
	if (!needle[0])
		return ((char *)haystack);
	else if (!haystack[0])
		return (NULL);
	while (i >= 0 && len >= 0)
	{
		j = len - 1;
		k = i;
		while (haystack[k] == needle[j] && k > len && k >= 0)
		{
			k--;
			j--;
		}
		if (j == 0)
			return ((char *)haystack + i);
		i--;
	}
	return (NULL);
}

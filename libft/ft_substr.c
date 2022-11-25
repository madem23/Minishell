/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anloisea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:18:44 by anloisea          #+#    #+#             */
/*   Updated: 2022/04/01 19:08:13 by anloisea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_check_len(char const *s, size_t len)
{
	if (len >= ft_strlen(s))
		return (ft_strlen(s));
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
	{
		sub = (char *)malloc(1 * sizeof(char));
		sub[i] = 0;
		return (sub);
	}
	sub = (char *)malloc((ft_check_len(s + start, len) + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	j = start;
	while (s[j] && i < len)
	{
		sub[i] = s[j];
		i++;
		j++;
	}
	sub[i] = 0;
	return (sub);
}

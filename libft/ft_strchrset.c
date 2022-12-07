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

#include "libft.h"

// Returns the index of the first occurence of a char.
int	locate_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-1);
	else
		return (i);
}

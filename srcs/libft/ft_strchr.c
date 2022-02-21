#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*string;

	string = (char *)s;
	while (*string != (char)c)
	{
		if (*string == '\0')
		{
			return (NULL);
		}
		string++;
	}
	return (string);
}

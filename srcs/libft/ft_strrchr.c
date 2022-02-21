#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*string;

	string = (char *)s + ft_strlen(s);
	while (*string != (char)c)
	{
		if (string == s)
		{
			return (NULL);
		}
		string--;
	}
	return (string);
}

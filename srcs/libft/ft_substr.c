#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*s_substring;
	size_t	i;

	i = 0;
	s_substring = (char *)malloc(len * sizeof(char) + 1);
	if (!s_substring || !s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		s_substring[0] = '\0';
		return (s_substring);
	}
	while (len)
	{
		s_substring[i++] = s[start++];
		len--;
	}
	s_substring[i] = '\0';
	return (s_substring);
}

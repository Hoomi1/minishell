#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s1_new;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	s1_new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s1_new)
		return (NULL);
	while (s1[i] && size != n)
	{
		s1_new[i] = s1[i];
		i++;
		size++;
	}
	s1_new[i] = '\0';
	return (s1_new);
}

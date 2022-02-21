#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_cmp;

	s1_cmp = NULL;
	if (s1)
	{
		s1_cmp = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
		if (!s1_cmp)
			return (NULL);
		ft_memcpy(s1_cmp, s1, ft_strlen(s1) + 1);
	}
	return (s1_cmp);
}

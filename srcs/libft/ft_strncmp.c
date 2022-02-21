#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	int		compare;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len <= s2_len)
		s1_len += 1;
	else
		s1_len = s2_len + 1;
	if (s1_len > n)
		s1_len = n;
	compare = ft_memcmp(s1, s2, s1_len);
	return (compare);
}

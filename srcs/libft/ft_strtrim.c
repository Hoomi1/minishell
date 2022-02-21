#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*s_trim;
	size_t	trim_len;

	trim_len = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (s1)
		trim_len = ft_strlen(s1);
	while (s1 && ft_strrchr(set, s1[trim_len]) && trim_len > 0)
		trim_len--;
	s_trim = ft_substr(s1, 0, trim_len + 1);
	return (s_trim);
}

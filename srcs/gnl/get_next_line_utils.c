#include "get_next_line.h"

size_t	ft_strlen(const char *src)
{
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*string;

	string = (char *)s;
	if (NULL == s)
		return (NULL);
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_string;
	char	*src_string;

	i = 0;
	dst_string = (char *)dst;
	src_string = (char *)src;
	if (NULL == src && NULL == dst)
		return (dst);
	while (i < n)
	{
		dst_string[i] = src_string[i];
		i++;
	}
	return (dst);
}

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

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s_new;

	if (!s1 || !s2)
		return (NULL);
	s_new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!s_new)
		return (NULL);
	ft_memcpy(s_new, s1, ft_strlen(s1));
	ft_memcpy(s_new + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (s_new);
}

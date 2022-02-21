#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_string;
	unsigned char	*src_string;

	i = 0;
	dst_string = (unsigned char *)dst;
	src_string = (unsigned char *)src;
	if (NULL == src && NULL == dst)
		return (dst);
	while (i < n)
	{
		dst_string[i] = src_string[i];
		if (src_string[i] == (unsigned char)c)
			return (&dst_string[i + 1]);
		i++;
	}
	return (NULL);
}

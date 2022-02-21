#include "libft.h"

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

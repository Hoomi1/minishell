#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	size_t	i;
	char	*dst_string;

	i = 0;
	dst_string = (char *)dst;
	while (i < n)
		dst_string[i++] = (unsigned char)c;
	return (dst_string);
}

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*src_string;
	unsigned char	c_symbol;

	src_string = (unsigned char *)src;
	c_symbol = (unsigned char)c;
	while (n--)
	{
		if (*src_string == c_symbol)
			return (src_string);
		src_string++;
	}
	return (NULL);
}

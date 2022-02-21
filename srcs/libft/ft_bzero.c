#include "libft.h"

void	ft_bzero(void *src, size_t n)
{
	size_t	i;
	char	*src_string;

	i = 0;
	src_string = (char *)src;
	while (i < n)
		src_string[i++] = '\0';
}

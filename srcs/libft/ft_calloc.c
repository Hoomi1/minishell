#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = (char *)malloc(count * size);
	if (!str)
		return (NULL);
	else
		ft_bzero(str, count * size);
	return (str);
}

#include "libft.h"

void	ft_putstr_fd(char *src, int fd)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		ft_putchar_fd(src[i], fd);
		i++;
	}
}

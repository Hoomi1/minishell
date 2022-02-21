#include "libft.h"

void	ft_putendl_fd(char *src, int fd)
{
	ft_putstr_fd(src, fd);
	ft_putchar_fd('\n', fd);
}

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return ((unsigned char)c);
	else
		return (0);
}

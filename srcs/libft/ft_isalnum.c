#include "libft.h"

int	ft_isalnum(int c)
{
	if ((unsigned char)c == ft_isalpha(c) || (unsigned char)c == ft_isdigit(c))
		return ((unsigned char)c);
	else
		return (0);
}

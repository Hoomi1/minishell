#include "libft.h"

int	ft_atoi(const char *s)
{
	int		res;
	int		sign;
	int		i;
	char	*str;

	res = 0;
	sign = 1;
	i = 0;
	str = (char *)s;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (i >= 20 && sign == 1)
			res = -1;
		if (i >= 20 && sign == -1)
			res = 0;
	}
	return (res * sign);
}

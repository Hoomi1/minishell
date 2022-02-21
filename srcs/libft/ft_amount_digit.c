#include "libft.h"

int	ft_amount_digit(int n)
{
	int	amount;
	int	number;

	number = n;
	amount = 0;
	if (n < 0 || n == 0)
		++amount;
	while (number)
	{
		number = number / 10;
		++amount;
	}
	return (amount);
}

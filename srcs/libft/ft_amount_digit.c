/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amount_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 06:00:18 by scanary           #+#    #+#             */
/*   Updated: 2021/04/10 04:23:47 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

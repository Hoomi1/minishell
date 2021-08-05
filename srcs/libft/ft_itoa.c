/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 23:08:49 by scanary           #+#    #+#             */
/*   Updated: 2021/04/10 02:30:11 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		++i;
	}
	return (i);
}

static int	ft_min(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		sign;

	sign = 0;
	len = length(n);
	if (n < 0)
	{
		len += 1;
		sign = -1;
	}
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(s))
		return (NULL);
	s[len] = '\0';
	while (len)
	{
		--len;
		s[len] = ft_min(n % 10) + '0';
		n = ft_min(n / 10);
	}
	if (sign == -1)
		s[0] = '-';
	return (s);
}

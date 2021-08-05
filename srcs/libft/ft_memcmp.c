/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:26:00 by scanary           #+#    #+#             */
/*   Updated: 2020/11/04 22:30:49 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_string;
	unsigned char	*s2_string;

	s1_string = (unsigned char *)s1;
	s2_string = (unsigned char *)s2;
	i = 0;
	if (s1_string == s2_string || n == 0)
		return (0);
	while (n--)
	{
		if (s1_string[i] != s2_string[i])
			return (s1_string[i] - s2_string[i]);
		i++;
	}
	return (0);
}

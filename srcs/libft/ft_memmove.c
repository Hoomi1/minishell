/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:23:14 by scanary           #+#    #+#             */
/*   Updated: 2020/11/04 19:14:43 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_string;
	unsigned char	*src_string;

	dst_string = (unsigned char *)dst;
	src_string = (unsigned char *)src;
	i = n;
	if (NULL == src_string && NULL == dst_string)
		return (dst);
	if (dst_string < src_string)
		return (ft_memcpy(dst_string, src_string, n));
	else
	{
		dst_string += i;
		src_string += i;
		while (i--)
			*--dst_string = *--src_string;
	}
	return (dst);
}

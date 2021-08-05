/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:08:19 by scanary           #+#    #+#             */
/*   Updated: 2021/04/10 02:31:15 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	size_t	i;
	char	*dst_string;

	i = 0;
	dst_string = (char *)dst;
	while (i < n)
		dst_string[i++] = (unsigned char)c;
	return (dst_string);
}

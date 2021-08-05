/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:50:43 by scanary           #+#    #+#             */
/*   Updated: 2020/11/17 15:28:49 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	size;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	while (dst[i] != '\0' && i < dstsize)
		i++;
	size = i;
	if (size == dstsize)
		return (size + src_len);
	while (src[i - size] && i < (dstsize - 1))
	{
		dst[i] = src[i - size];
		i++;
	}
	if (size < dstsize)
		dst[i] = '\0';
	return (size + src_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:26:57 by scanary           #+#    #+#             */
/*   Updated: 2020/11/05 04:51:01 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s2_len;

	if (*s2 == '\0')
		return ((char *)s1);
	s2_len = ft_strlen(s2);
	while (*s1 != '\0' && len-- >= s2_len)
	{
		if (*s1 == *s2 && ft_memcmp(s1, s2, s2_len) == 0)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:53:53 by scanary           #+#    #+#             */
/*   Updated: 2020/11/07 00:35:46 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s_new;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s_new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!s_new)
		return (NULL);
	ft_memcpy(s_new, s1, ft_strlen(s1));
	ft_memcpy(s_new + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (s_new);
}

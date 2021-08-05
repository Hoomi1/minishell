/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:29:42 by scanary           #+#    #+#             */
/*   Updated: 2021/07/26 12:30:02 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_cmp;

	s1_cmp = NULL;
	if (s1)
	{
		s1_cmp = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
		if (!s1_cmp)
			return (NULL);
		ft_memcpy(s1_cmp, s1, ft_strlen(s1) + 1);
	}
	return (s1_cmp);
}

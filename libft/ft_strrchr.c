/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:05:26 by cyuuki            #+#    #+#             */
/*   Updated: 2021/04/26 20:53:44 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	l;

	l = ft_strlen((char *)str) + 1;
	while (l--)
	{
		if ((unsigned char)*(str + l) == (unsigned char)ch)
			return ((char *)(str + l));
	}
	return (NULL);
}

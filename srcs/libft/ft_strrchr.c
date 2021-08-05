/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:11:45 by scanary           #+#    #+#             */
/*   Updated: 2020/11/05 04:24:40 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*string;

	string = (char *)s + ft_strlen(s);
	while (*string != (char)c)
	{
		if (string == s)
		{
			return (NULL);
		}
		string--;
	}
	return (string);
}

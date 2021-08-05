/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 03:41:44 by scanary           #+#    #+#             */
/*   Updated: 2020/11/12 04:08:04 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = ft_strdup((const char *)s);
	if (str == NULL)
		return (NULL);
	while (str[i] != 0)
	{
		str[i] = f((unsigned int)i, str[i]);
		i++;
	}
	return (str);
}

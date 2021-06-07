/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:00:58 by cyuuki            #+#    #+#             */
/*   Updated: 2021/04/26 20:50:45 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int		i;
	char	*str2;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
		{
			str2 = (char *)&str[i];
			return (str2);
		}
		i++;
	}
	if (str[i] == ch)
	{
		str2 = (char *)&str[i];
		return (str2);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:26:21 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 13:43:22 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr(char **array)
{
	size_t	i;

	i = 0;
	if (*array)
	{
		while (array[i])
		{
			ft_free_tmp(array[i]);
			i++;
		}
		free(array);
		array = NULL;
	}
}

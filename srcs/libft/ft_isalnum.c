/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 06:25:37 by scanary           #+#    #+#             */
/*   Updated: 2020/11/05 06:32:51 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((unsigned char)c == ft_isalpha(c) || (unsigned char)c == ft_isdigit(c))
		return ((unsigned char)c);
	else
		return (0);
}

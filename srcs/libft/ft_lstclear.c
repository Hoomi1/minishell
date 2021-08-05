/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 01:01:54 by scanary           #+#    #+#             */
/*   Updated: 2020/11/08 01:50:26 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst && *lst && del)
	{
		if ((**lst).next)
			ft_lstclear(&(**lst).next, del);
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
}

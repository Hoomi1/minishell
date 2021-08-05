/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 02:12:52 by scanary           #+#    #+#             */
/*   Updated: 2020/11/09 19:20:50 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*lst_new;
	t_list	*lst_dub;
	t_list	*lst_f;

	if (!lst || !f)
		return (NULL);
	lst_dub = lst;
	lst_new = NULL;
	while (lst_dub)
	{
		if (f((*lst_dub).content))
		{
			lst_f = ft_lstnew(f((*lst_dub).content));
			if (!lst_f)
			{
				ft_lstclear(&lst_dub, del);
				return (NULL);
			}
			ft_lstadd_back(&lst_new, lst_f);
		}
		lst_dub = (*lst_dub).next;
	}
	return (lst_new);
}

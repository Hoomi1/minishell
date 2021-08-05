/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:10:39 by scanary           #+#    #+#             */
/*   Updated: 2021/04/10 02:31:44 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list **lst)
{
	t_list	*del;
	t_list	*temp;

	if (*lst == NULL)
		return ;
	temp = *lst;
	while (temp)
	{
		del = temp;
		temp = temp->next;
		free(del->content);
		del->content = NULL;
		free(del);
		del = NULL;
	}
	lst = NULL;
}

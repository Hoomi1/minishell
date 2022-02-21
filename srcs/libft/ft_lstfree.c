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

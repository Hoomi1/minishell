#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == 0)
		return (lst);
	last = lst;
	while ((*last).next)
		last = (*last).next;
	return (last);
}

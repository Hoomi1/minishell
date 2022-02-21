#include "libft.h"

void	ft_free_tmp(char *tmp)
{
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
}

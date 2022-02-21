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

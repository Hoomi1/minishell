#include "minishell.h"

void	clear_buffer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
}

void	write_list(char *str_list)
{
	refactor(str_list);
	list_next(str_list);
}

void	keyhuck_str(char *buffer, t_str *str)
{
	char	*temp;

	str->buffer_str = ft_strjoin(str->buffer_str, buffer);
	str->i = ft_strlen(str->buffer_str);
	str->lef_rig = str->lef_rig + 1;
	if (str->lef_rig != str->i)
		str->i = str->lef_rig;
	if (str->del > 0)
		str->del = str->del - 1;
	temp = str->buffer_str;
	if (temp && ft_strchr(temp, '\n') == NULL)
		free(temp);
}

int	str_alfa(char *buffer)
{
	int	i;

	i = 0;
	if (ft_isprint(buffer[i]) || buffer[i] == '\n')
		return (0);
	return (-1);
}

int	sizetwo(t_listtwo *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		++size;
		lst = (*lst).next;
	}
	return (size);
}

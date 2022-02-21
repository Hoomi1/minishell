#include "minishell.h"

void	settin_par(t_str *str)
{
	str->i = 0;
	str->fd = 0;
	str->lef_rig = 0;
	str->del = 0;
	str->buffer_str = (char *)ft_calloc(2, (sizeof(char)));
	g_gl.flag = 0;
	g_gl.size_i = 12;
	g_gl.status_exit = 0;
}

int	settin_term(void)
{
	int	count;

	g_gl.load_attributes.c_lflag &= ~(ISIG);
	tcgetattr(0, &g_gl.load_attributes);
	tcgetattr(0, &g_gl.saved_attributes);
	g_gl.saved_attributes.c_lflag &= ~(ECHO);
	g_gl.saved_attributes.c_lflag &= ~(ICANON);
	g_gl.saved_attributes.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &g_gl.saved_attributes);
	count = tgetent(0, "xterm-256color");
	if (count < 0)
		return (-1);
	return (count);
}

void	histdupview(char *file, t_str *str)
{
	int		size;
	char	*view;

	if (stat(file, &g_gl.buf) == 0)
	{
		if (str->fd == 0)
		{
			str->fd = open(file, O_RDWR);
			size = 1;
			while (size)
			{
				size = get_next_line(str->fd, &view);
				refactor(view);
				list_next(view);
				free(view);
			}
			g_gl.flag = 1;
		}
	}
}

void	refactor(char *buffer_str)
{
	int	i;

	i = 0;
	while (buffer_str[i] != '\0')
	{
		if (buffer_str[i] == '\n')
		{
			buffer_str[i] = '\0';
			break ;
		}
		i++;
	}
}

t_listtwo	*list_next(char *strh)
{
	t_listtwo	*newlist;
	char		*str;

	str = ft_strdup(strh);
	newlist = (t_listtwo *)malloc(sizeof(t_listtwo));
	newlist->next = NULL;
	newlist->prev = NULL;
	newlist->str = str;
	if (g_gl.head == NULL)
	{
		g_gl.head = newlist;
		g_gl.tail = newlist;
	}
	else
	{
		g_gl.tail->next = newlist;
		newlist->prev = g_gl.tail;
		g_gl.tail = newlist;
	}
	return (g_gl.head);
}

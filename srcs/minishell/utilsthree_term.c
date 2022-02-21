#include "minishell.h"

void	bufadd(t_str *str, t_history *histor)
{
	if (histor->buffer_list)
	{
		if (g_gl.flag == 1 && ft_strncmp(histor->buffer_list, "\n", 1))
		{
			write(str->fd, histor->buffer_list, ft_strlen(histor->buffer_list));
			refactor(histor->buffer_list);
			list_next(histor->buffer_list);
			free(histor->buffer_list);
			histor->buffer_list = NULL;
		}
	}
	free(histor->pwd);
	free(histor->file);
	histor->pwd = NULL;
	histor->file = NULL;
}

void	signal_my(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

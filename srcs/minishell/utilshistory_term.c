#include "minishell.h"

static void	init_file_histor(t_history *histor, t_str *str, t_data *data)
{
	histor->pwd = NULL;
	histor->pwd = ft_strdup("/direct_history/temp_history");
	if (histor->pwd == NULL)
	{
		ft_free_tmp(str->buffer_str);
		shell_exit(data, NULL, "malloc: *** error", 1);
	}
	histor->file = NULL;
	histor->file = ft_strjoin(data->envp[data->current_pwd] + 4, histor->pwd);
	if (histor->file == NULL)
	{
		ft_free_tmp(histor->pwd);
		ft_free_tmp(str->buffer_str);
		shell_exit(data, NULL, "malloc: *** error", 1);
	}
	histor->buffer_list = NULL;
	histor->buffer_list = ft_strdup(str->buffer_str);
	if (histor->buffer_list == NULL)
	{
		ft_free_tmp(histor->file);
		ft_free_tmp(histor->pwd);
		ft_free_tmp(str->buffer_str);
		shell_exit(data, NULL, "malloc: *** error", 1);
	}
}

static void	fd_state(char *file, t_str *str)
{
	if (stat(file, &g_gl.buf) == -1)
	{
		str->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
		g_gl.flag = 1;
	}
}

static void	freehistory(t_history *histor)
{
	if (histor->pwd != NULL)
		ft_free_tmp(histor->pwd);
	if (histor->file != NULL)
		ft_free_tmp(histor->file);
	if (histor->buffer_list != NULL)
		ft_free_tmp(histor->buffer_list);
}

static int	check_file(t_str *str, t_history *histor)
{
	int	size;

	size = 1;
	while (size)
	{
		size = get_next_line(str->fd, &histor->str_list);
		if (size == -1)
		{
			freehistory(histor);
			return (-1);
		}
		write_list(histor->str_list);
	}
	return (0);
}

int	my_history(t_str *str, t_data *data)
{
	t_history	histor;

	init_file_histor(&histor, str, data);
	if (stat(histor.file, &g_gl.buf) == -1)
		fd_state(histor.file, str);
	else if (stat(histor.file, &g_gl.buf) == 0)
	{
		if (str->fd == 0)
		{
			str->fd = open(histor.file, O_RDWR);
			check_file(str, &histor);
			write_list(histor.str_list);
			g_gl.flag = 1;
		}
	}
	bufadd(str, &histor);
	freehistory(&histor);
	return (0);
}

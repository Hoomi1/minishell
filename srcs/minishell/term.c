#include "minishell.h"

static void	keyhuck(char *buffer, t_str *str, t_data *data)
{	
	if (str_alfa(buffer) == 0)
	{
		keyhuck_str(buffer, str);
		g_gl.flag = 1;
	}
	if (ft_strchr(str->buffer_str, '\n') != NULL || g_gl.signal == 1)
		key_history(str, data);
	else if (!ft_strncmp(buffer, "\e[A", 3) && g_gl.head != NULL)
		keyhuck_up(buffer, str);
	else if (!ft_strncmp(buffer, "\e[B", 3) && g_gl.head != NULL)
		keyhuck_down(buffer, str);
}

static void	infin_while(char *buffer, t_str *str, int count, t_data *data)
{
	while (1)
	{	
		signal_my();
		if (!ft_strncmp(buffer, "\003", 1))
		{
			str->buffer_str = "";
			write(0, "\nminishell->", 12);
			tputs(save_cursor, 1, ft_putchar);
		}
		clear_buffer(buffer);
		count = read(0, buffer, BUFFER_SIZE_MINI);
		if ((count >= 1) && ft_strncmp(buffer, "\t", 1) != 0 && \
			ft_strncmp(buffer, "\e[C", 3) != 0 \
				&& ft_strncmp(buffer, "\e[D", 3) != 0 \
					&& ft_strncmp(buffer, "\x7f", 3) != 0)
			write(1, buffer, BUFFER_SIZE_MINI);
		keyhuck(buffer, str, data);
		if (!ft_strncmp(buffer, "\4", 1) && !ft_strncmp(str->buffer_str, "", 1))
		{	
			write(1, "exit\n", 5);
			tcsetattr(0, TCSANOW, &g_gl.load_attributes);
			exit(g_gl.status_exit);
		}
	}
}

static void	history_view(t_str *str, t_data *data)
{
	char	*file;
	char	*pwd;

	pwd = ft_strdup("/direct_history/temp_history");
	file = ft_strjoin(data->envp[data->current_pwd] + 4, pwd);
	histdupview(file, str);
	if (g_gl.head)
	{
		while (g_gl.head->next != NULL && g_gl.head)
			g_gl.head = g_gl.head->next;
	}
	free(pwd);
	free(file);
}

static int	read_line(t_data *data)
{
	char	*buffer;
	int		count;
	t_str	str;
	char	*tmp;

	settin_par(&str);
	buffer = (char *) ft_calloc(BUFFER_SIZE_MINI, sizeof(char));
	if (!buffer)
		return (-1);
	count = settin_term();
	write(1, "minishell->", 11);
	tputs(save_cursor, 1, ft_putchar);
	history_view(&str, data);
	tmp = str.buffer_str;
	infin_while(buffer, &str, count, data);
	free(buffer);
	free(tmp);
	return (0);
}

int	term(t_data *data)
{
	read_line(data);
	tcgetattr(0, &g_gl.saved_attributes);
	g_gl.saved_attributes.c_lflag |= ECHO;
	g_gl.saved_attributes.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &g_gl.saved_attributes);
	return (0);
}

#include "minishell.h"

static int	shell_error_point(char *str, char *token)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

int	check_point(char *str)
{
	if (!ft_strcmp("/.", str) || !ft_strcmp("/..", str) || \
	!ft_strcmp("./", str) || !ft_strcmp("../", str))
	{
		g_gl.status_exit = 126;
		return (shell_error_point("is a directory", str));
	}
	else if (!ft_strcmp(".", str))
	{
		g_gl.status_exit = 2;
		return (shell_error_point(ERR_1, str));
	}
	else if (!ft_strcmp("..", str))
	{
		g_gl.status_exit = 127;
		return (shell_error_point("command not found", str));
	}
	return (0);
}

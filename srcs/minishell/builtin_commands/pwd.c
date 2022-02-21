#include "../minishell.h"

void	ft_pwd(t_data *data, t_commands *commands)
{
	char	dir[1024];

	if (getcwd(dir, 1024) != NULL)
		ft_putendl_fd(dir, 1);
	else
		shell_exit(data, commands, "getcwd() function shall fail", 1);
}

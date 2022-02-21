#include "../minishell.h"

void	echo_print(t_commands *commands)
{
	int	i;

	i = 1;
	while (commands->cmd_arr[i] != NULL)
	{
		if (commands->cmd_arr[i + 1] == NULL)
			ft_putstr_fd(commands->cmd_arr[i], 1);
		else
		{
			ft_putstr_fd(commands->cmd_arr[i], 1);
			ft_putstr_fd(" ", 1);
		}
		i++;
	}
	ft_putendl_fd("", 1);
}

void	ft_echo(t_commands *commands)
{
	int	i;

	i = 1;
	if (commands->cmd_arr[1] == NULL)
		ft_putendl_fd("", 1);
	else if (ft_strcmp("-n", commands->cmd_arr[1]) == 0)
	{
		i++;
		while (commands->cmd_arr[i] != NULL)
		{
			if (commands->cmd_arr[i + 1] == NULL)
				ft_putstr_fd(commands->cmd_arr[i], 1);
			else
			{
				ft_putstr_fd(commands->cmd_arr[i], 1);
				ft_putstr_fd(" ", 1);
			}
			i++;
		}
	}
	else
		echo_print(commands);
	g_gl.status_exit = 0;
}

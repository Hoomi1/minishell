#include "minishell.h"

static void	my_init(int num)
{
	if (num == SIGINT && g_gl.flag_cat == 0)
	{
		printf("\n");
		write(1, "minishell->", 11);
		tputs(save_cursor, 1, ft_putchar);
	}
	if (num == SIGQUIT && g_gl.flag_cat == 0)
		ft_putstr_fd("", 0);
	if (num == SIGINT && g_gl.flag_cat == 1)
	{
		ft_putendl_fd("", 0);
		g_gl.flag_cat = 0;
	}
	if (num == SIGQUIT && g_gl.flag_cat == 1)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_gl.flag_cat = 0;
	}
}

static void	is_childpid(t_data *data, t_commands *commands, char *command)
{
	if (execve(command, commands->cmd_arr, data->envp) < 0)
	{
		ft_free_tmp(command);
		shell_exit(data, commands, (strerror(errno)), EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
}

static void	prosess_in_path(t_data *data, t_commands *commands)
{
	char	*command;

	tcsetattr(0, TCSANOW, &g_gl.load_attributes);
	signal(SIGQUIT, my_init);
	signal(SIGINT, my_init);
	commands->pid = fork();
	if (commands->pid < 0)
		shell_exit(data, commands, (strerror(errno)), 1);
	else if (commands->pid == 0)
	{
		command = ft_strjoin(commands->cmd_dir, commands->cmd);
		if (command == NULL)
			shell_exit(data, commands, "malloc: *** error", 1);
		is_childpid(data, commands, command);
		ft_free_tmp(command);
	}
}

static void	error_command(t_data *data, t_commands *commands)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(commands->cmd_arr[0], 2);
	if (commands->cmd_dir && data->envp[data->path])
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": command not found", 2);
	g_gl.status_exit = 127;
}

void	prosess_command(t_data *data, t_commands *commands)
{
	g_gl.flag_cat = 0;
	if (commands->type_cmd == CMD_IN_EXECVE)
	{
		g_gl.flag_cat = 1;
		prosess_in_path(data, commands);
	}
	else if (commands->type_cmd == CMD_CD)
		ft_cd(data, commands);
	else if (commands->type_cmd == CMD_PWD)
		ft_pwd(data, commands);
	else if (commands->type_cmd == CMD_ECHO)
		ft_echo(commands);
	else if (commands->type_cmd == CMD_EXPORT)
		ft_export(commands, data);
	else if (commands->type_cmd == CMD_UNSET)
		ft_unset(commands, data);
	else if (commands->type_cmd == CMD_ENV)
		ft_env(commands, data);
	else if (commands->type_cmd == CMD_EXIT)
		ft_exit(commands, data);
	else if (commands->type_cmd == CMD_ERROR)
		error_command(data, commands);
}

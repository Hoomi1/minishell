#include "minishell.h"

static void	cmd_tolower(t_commands *commands)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = commands->cmd;
	while (tmp[i] != '\0')
	{
		if (ft_isalpha(tmp[i]))
			if (tmp[i] >= 'A' && tmp[i] <= 'Z')
				tmp[i] += 32;
		i++;
	}
}

static void	define_type_command(t_commands *commands)
{
	cmd_tolower(commands);
	if (!(ft_strcmp("cd", commands->cmd)))
		commands->type_cmd = CMD_CD;
	else if (!(ft_strcmp("echo", commands->cmd)))
		commands->type_cmd = CMD_ECHO;
	else if (!(ft_strcmp("env", commands->cmd)))
		commands->type_cmd = CMD_ENV;
	else if (!(ft_strcmp("exit", commands->cmd)))
		commands->type_cmd = CMD_EXIT;
	else if (!(ft_strcmp("export", commands->cmd)))
		commands->type_cmd = CMD_EXPORT;
	else if (!(ft_strcmp("pwd", commands->cmd)))
		commands->type_cmd = CMD_PWD;
	else if (!(ft_strcmp("unset", commands->cmd)))
		commands->type_cmd = CMD_UNSET;
	else
		commands->type_cmd = CMD_IN_EXECVE;
}

void	full_info_command(t_data *data, t_commands *commands)
{
	t_commands	*tmp_cmd;

	tmp_cmd = commands;
	if (tmp_cmd->cmd_arr[0])
	{
		tmp_cmd->cmd = ft_strdup(tmp_cmd->cmd_arr[0]);
		if (tmp_cmd->cmd == NULL)
			shell_exit(data, commands, "malloc: *** error", 1);
		define_type_command(tmp_cmd);
		if (tmp_cmd->type_cmd == CMD_IN_EXECVE)
			search_for_commands(commands, data);
		if (tmp_cmd->pipe)
			full_info_command(data, tmp_cmd->pipe);
	}
	else if (tmp_cmd->next_token_pipe)
		full_info_command(data, tmp_cmd->pipe);
}

void	parser_command_test(t_data *data, t_commands *commands, t_list *tokens)
{
	int	find_error;

	find_error = find_command(data, commands, tokens, NULL);
	if (find_error)
	{
		ft_lstfree(&tokens);
		shell_exit(data, commands, "malloc: *** error", 1);
	}
	ft_lstfree(&tokens);
	find_error = parser_quotes_and_dollar(data, commands);
	if (find_error)
		shell_exit(data, commands, "malloc: *** error", 1);
	full_info_command(data, commands);
}

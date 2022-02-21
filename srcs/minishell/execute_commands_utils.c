#include "minishell.h"

int	get_heredoc(char *stop_work)
{
	int		fd;
	char	*line;
	int		gnl;

	fd = open("heredoc", O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	line = NULL;
	gnl = 1;
	while (gnl)
	{
		write(1, "> ", 2);
		get_next_line(0, &line);
		if (!(ft_strcmp(line, stop_work)))
			gnl = 0;
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		ft_free_tmp(line);
	}
	close(fd);
	fd = open("heredoc", O_RDONLY);
	return (fd);
}

void	redirect_end(t_commands *cmd, int *fd_redir_write, \
						int *fd_redir_read)
{
	t_redirects	*redirect;

	redirect = cmd->redir;
	while (redirect)
	{
		if (redirect && (redirect->type_redir == REDIR_RIGHT_1 || \
		redirect->type_redir == REDIR_RIGHT_2))
		{
			if (redirect->type_redir == REDIR_RIGHT_1)
				*fd_redir_write = open(redirect->content, O_CREAT | \
				O_RDWR | O_TRUNC, S_IRWXU);
			if (redirect->type_redir == REDIR_RIGHT_2)
				*fd_redir_write = open(redirect->content, O_CREAT | \
				O_RDWR | O_APPEND, S_IRWXU);
		}
		if (redirect && (redirect->type_redir == REDIR_LEFT_1 || \
		redirect->type_redir == REDIR_LEFT_2))
		{
			if (redirect->type_redir == REDIR_LEFT_1)
				*fd_redir_read = open(redirect->content, O_RDONLY, S_IREAD);
			if (redirect->type_redir == REDIR_LEFT_2)
				*fd_redir_read = get_heredoc(redirect->content);
		}
		redirect = redirect->next;
	}
}

void	completion_cmd_line(t_data *data, t_commands *commands)
{
	t_commands	*cmd;
	int			status;

	cmd = commands;
	if (cmd->next_token_pipe && cmd->pid)
	{
		if (waitpid(cmd->pid, &status, WNOHANG) == -1)
			shell_exit(data, commands, (strerror(errno)), 1);
		if (cmd->pipe)
			completion_cmd_line(data, cmd->pipe);
	}
	else if (!cmd->next_token_pipe && cmd->pid)
	{
		if (waitpid(cmd->pid, &status, WUNTRACED) == -1)
			shell_exit(data, commands, (strerror(errno)), 1);
		if (WIFEXITED(status))
			g_gl.status_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_gl.status_exit = 128 + WTERMSIG(status);
		else if (WIFSTOPPED(status))
			g_gl.status_exit = WSTOPSIG(status);
		dup2(data->fd1, 1);
		dup2(data->fd0, 0);
	}
}

#include "minishell.h"

static void	pipe_end(t_data *data, t_commands *pip, int fd0, int fd1)
{
	dup2(fd0, 0);
	if (fd1 != 0)
		close(fd1);
	if (fd0 != 0)
		close(fd0);
	if (pip->pipe)
	{
		close(1);
		dup2(data->fd1, 1);
		execute_cmd_line(data, pip->pipe);
	}
}

static void	execute_redirects(t_commands *commands, \
							int *fd_redir_write, int *fd_redir_read)
{
	redirect_end(commands, fd_redir_write, fd_redir_read);
	if (commands->cmd || commands->next_token_redir)
	{
		if (*fd_redir_write == -1 || *fd_redir_read == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(commands->redir->content, 2);
			ft_putendl_fd(": No such file or directory", 2);
			g_gl.status_exit = 1;
		}
		if (*fd_redir_write > 0)
			dup2(*fd_redir_write, 1);
		if (*fd_redir_read > 0)
			dup2(*fd_redir_read, 0);
	}
}

static void	close_fd_redir(int fd_redir_write, int fd_redir_read)
{
	if (fd_redir_write)
		close(fd_redir_write);
	if (fd_redir_read)
		close(fd_redir_read);
	unlink("heredoc");
}

void	execute_cmd_line(t_data *data, t_commands *commands)
{
	int			fd[2];
	int			fd_redir_write;
	int			fd_redir_read;
	t_commands	*pip;

	init_fd_command(fd, &fd_redir_write, &fd_redir_read);
	if (commands->cmd || commands->next_token_redir)
	{
		pip = commands;
		if (pip->pipe)
		{
			pipe(fd);
			dup2(fd[1], 1);
		}
		if (commands->next_token_redir)
			execute_redirects(commands, &fd_redir_write, &fd_redir_read);
		if ((commands->cmd || commands->next_token_pipe) && \
		fd_redir_write >= 0 && fd_redir_read >= 0)
		{
			prosess_command(data, commands);
			close_fd_redir(fd_redir_write, fd_redir_read);
			pipe_end(data, pip, fd[0], fd[1]);
		}
	}
}

void	execute_commands(t_data *data, t_commands *commands)
{
	t_commands	*tmp_cmds;

	tmp_cmds = commands;
	if (tmp_cmds)
	{
		execute_cmd_line(data, tmp_cmds);
		completion_cmd_line(data, commands);
		dup2(data->fd1, 1);
		dup2(data->fd0, 0);
	}
}

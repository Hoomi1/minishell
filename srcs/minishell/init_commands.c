/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:12:19 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 18:17:18 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command_dir(t_commands *commands, t_data *data, \
								char **split_path, char *dir_path)
{
	char	*tmp;

	tmp = ft_strdup("/");
	if (tmp == NULL)
	{
		ft_free_arr(split_path);
		shell_exit(data, commands, "malloc: *** error", 1);
	}
	commands->cmd_dir = ft_strjoin(dir_path, tmp);
	if (commands->cmd_dir == NULL)
	{
		ft_free_arr(split_path);
		shell_exit(data, commands, "malloc: *** error", 1);
	}
	ft_free_tmp(tmp);
}

void	init_fd_command(int *fd, int *fd_redir_write, int *fd_redir_read)
{
	fd[0] = 0;
	fd[1] = 0;
	*fd_redir_write = 0;
	*fd_redir_read = 0;
}

t_redirects	*init_struct_redir(void)
{
	t_redirects	*new_redir;

	new_redir = (t_redirects *)malloc(sizeof(t_redirects));
	if (new_redir == NULL)
		return (NULL);
	new_redir->type_redir = -1;
	new_redir->content = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

t_commands	*init_struct_commands(void)
{
	t_commands	*new_commands;

	new_commands = (t_commands *)malloc(sizeof(t_commands));
	if (new_commands == NULL)
		return (NULL);
	new_commands->cmd = NULL;
	new_commands->type_cmd = -1;
	new_commands->pid = 0;
	new_commands->cmd_dir = NULL;
	new_commands->cmd_arr = NULL;
	new_commands->count_args_for_cmd = -1;
	new_commands->next_token_redir = 0;
	new_commands->next_token_pipe = 0;
	new_commands->redir = NULL;
	new_commands->pipe = NULL;
	return (new_commands);
}

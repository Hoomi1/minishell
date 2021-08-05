/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:05:02 by scanary           #+#    #+#             */
/*   Updated: 2021/07/21 05:59:11 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_full_path(t_commands *commands, t_data *data, char **split_path)
{
	char		*is_full;
	char		*tmp;

	is_full = ft_strrchr(commands->cmd, '/');
	if (is_full)
	{
		is_full++;
		tmp = commands->cmd;
		commands->cmd = ft_strdup(is_full);
		if (commands->cmd == NULL)
		{
			ft_free_tmp(tmp);
			ft_free_arr(split_path);
			shell_exit(data, commands, "malloc: *** error", 1);
		}
		commands->cmd_dir = ft_strndup(tmp, is_full - tmp);
		if (commands->cmd_dir == NULL)
		{
			ft_free_tmp(tmp);
			ft_free_arr(split_path);
			shell_exit(data, commands, "malloc: *** error", 1);
		}
		ft_free_tmp(tmp);
	}
}

static void	close_dir_in_path(t_data *data, t_commands *commands, \
							char **split_path, DIR *dir)
{
	if ((closedir(dir)) == -1)
	{
		ft_free_arr(split_path);
		shell_exit(data, commands, "closedir: *** error", 1);
	}
}

static int	existence_test(t_commands *commands, t_data *data, \
							char **split_path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				status;
	int				existence;

	existence = 0;
	dir = opendir(commands->cmd_dir);
	if (dir)
	{
		status = 1;
		while (status)
		{
			entry = readdir(dir);
			if (entry)
			{
				if (!(ft_strcmp(entry->d_name, commands->cmd)))
					existence = 1;
			}
			else
				status = 0;
		}
		close_dir_in_path(data, commands, split_path, dir);
	}
	return (existence);
}

static void	read_splitpath(t_commands *commands, t_data *data, \
								char **split_path, char *dir_path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				status;

	dir = opendir(dir_path);
	if (dir)
	{
		status = 1;
		while (status)
		{
			entry = readdir(dir);
			if (entry)
			{
				if (!(ft_strcmp(entry->d_name, commands->cmd)))
					init_command_dir(commands, data, split_path, dir_path);
			}
			else
				status = 0;
		}
		close_dir_in_path(data, commands, split_path, dir);
	}
}

void	search_for_commands(t_commands *commands, t_data *data)
{
	char	**split_path;
	size_t	i;

	split_path = ft_split(data->envp[data->path] + 5, ':');
	if (split_path == NULL)
		shell_exit(data, commands, "malloc: *** error", 1);
	is_full_path(commands, data, split_path);
	if (commands->cmd_dir && !existence_test(commands, data, split_path))
		commands->type_cmd = CMD_ERROR;
	i = 0;
	while (split_path[i] && commands->cmd_dir == NULL)
	{
		read_splitpath(commands, data, split_path, split_path[i]);
		i++;
	}
	if (commands->cmd_dir == NULL)
		commands->type_cmd = CMD_ERROR;
	ft_free_arr(split_path);
}

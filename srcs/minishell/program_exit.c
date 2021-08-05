/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 01:27:35 by scanary           #+#    #+#             */
/*   Updated: 2021/07/28 19:20:48 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freelist(void *exp)
{
	t_listexp	*p;

	p = exp;
	if (p->name)
		free(p->name);
	if (p->value)
		free(p->value);
	free(p);
}

void	freeing_memory_data(t_data *data)
{
	if (data)
	{
		ft_free_tmp(data->input);
		ft_free_arr(data->envp);
		ft_lstclear(&data->list_envp, freelist);
		free(data);
		data = NULL;
	}
}

void	freeing_memory_redirects(t_redirects *redir)
{
	if (redir)
	{
		ft_free_tmp(redir->content);
		freeing_memory_redirects(redir->next);
		free(redir);
		redir = NULL;
	}
}

void	freeing_memory_commands(t_commands *commands)
{
	if (commands)
	{
		ft_free_tmp(commands->cmd);
		ft_free_tmp(commands->cmd_dir);
		ft_free_arr(commands->cmd_arr);
		if (commands->cmd_arr[0] == NULL)
			free(commands->cmd_arr);
		freeing_memory_commands(commands->pipe);
		freeing_memory_redirects(commands->redir);
		free(commands);
		commands = NULL;
	}
}

int	shell_exit(t_data *data, t_commands *commands, char *str, int num)
{
	ft_putendl_fd(str, 2);
	if (data)
		freeing_memory_data(data);
	if (commands)
		freeing_memory_commands(commands);
	exit(num);
}

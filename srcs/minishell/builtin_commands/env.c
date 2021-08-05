/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 23:05:36 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 19:17:13 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_commands *commands, t_data *data)
{
	t_list	*list;

	list = data->list_envp;
	if (commands->cmd_arr[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", commands->cmd_arr[1]);
		g_gl.status_exit = 127;
	}
	else
	{
		while (list->next != NULL)
		{
			if (((t_listexp *)list->content)->value)
				printf("%s=%s\n", ((t_listexp *)list->content)->name, \
					((t_listexp *)list->content)->value);
			list = list->next;
		}
		if (((t_listexp *)list->content)->value)
			printf("%s=%s\n", ((t_listexp *)list->content)->name, \
				((t_listexp *)list->content)->value);
	}
}

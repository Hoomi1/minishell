/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:06:57 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/27 19:17:19 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	succes_exit(t_data *data, t_commands *commands, int fl_exit)
{
	if (fl_exit == 0)
	{
		tcsetattr(0, TCSANOW, &g_gl.load_attributes);
		freeing_memory_commands(commands);
		freeing_memory_data(data);
		exit(g_gl.status_exit);
	}
}

void	prover_exit(t_commands *commands, int *fl_exit, int i)
{
	if (i == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", \
		commands->cmd_arr[1]);
		g_gl.status_exit = 255;
		*fl_exit = 0;
	}
	if (commands->cmd_arr[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		*fl_exit = 1;
	}
}

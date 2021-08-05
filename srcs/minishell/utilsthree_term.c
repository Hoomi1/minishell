/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsthree_term.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:42:18 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/27 19:17:01 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bufadd(t_str *str, t_history *histor)
{
	if (histor->buffer_list)
	{
		if (g_gl.flag == 1 && ft_strncmp(histor->buffer_list, "\n", 1))
		{
			write(str->fd, histor->buffer_list, ft_strlen(histor->buffer_list));
			refactor(histor->buffer_list);
			list_next(histor->buffer_list);
			free(histor->buffer_list);
			histor->buffer_list = NULL;
		}
	}
	free(histor->pwd);
	free(histor->file);
	histor->pwd = NULL;
	histor->file = NULL;
}

void	signal_my(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

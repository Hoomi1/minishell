/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:43:47 by scanary           #+#    #+#             */
/*   Updated: 2021/07/24 17:01:01 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data *data, t_commands *commands)
{
	char	dir[1024];

	if (getcwd(dir, 1024) != NULL)
		ft_putendl_fd(dir, 1);
	else
		shell_exit(data, commands, "getcwd() function shall fail", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:44:22 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 19:17:05 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_cd(char *str_cd)
{
	printf("minishell: cd: %s: %s\n", str_cd, strerror(errno));
	g_gl.status_exit = 1;
}

static char	*outputofall(char *name, t_data *data)
{
	int		sum;
	char	*rename;
	t_list	*new_list;

	new_list = data->list_envp;
	while (new_list->next)
	{
		rename = lnew_name(new_list);
		sum = ft_strcmp(name, rename);
		if (!sum)
			return (lnew_value(new_list));
		new_list = new_list->next;
	}
	return (NULL);
}

static void	treatment(t_data *data, t_commands *commands)
{
	char	*znach;

	data->envp[data->home_dir] = \
	getcwd(data->envp[data->home_dir], 200);
	if (data->envp[data->home_dir] == NULL)
		shell_exit(data, commands, "getcwd() function shall fail", 1);
	znach = outputofall("PWD", data);
	if (znach)
	{
		cheak_value("OLDPWD", znach, &data->list_envp);
		cheak_value("PWD", data->envp[data->home_dir], &data->list_envp);
	}
}

void	ft_cd(t_data *data, t_commands *commands)
{
	char	*str_cd;
	int		len;

	if (commands->count_args_for_cmd > 0)
	{
		str_cd = commands->cmd_arr[1];
		if (*str_cd == '.' && *(str_cd + 1) == '.')
		{
			len = ft_strlen(data->envp[data->home_dir]);
			while (data->envp[data->home_dir][len] != '/')
				len--;
			len--;
			data->envp[data->home_dir][len] = '\0';
		}
		if (chdir(str_cd) == 0)
			treatment(data, commands);
		else
			write_cd(str_cd);
	}
}

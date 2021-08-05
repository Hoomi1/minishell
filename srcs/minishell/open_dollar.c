/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:48:34 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 19:13:49 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*name_not_from_envp(char *name)
{
	char	*str;

	if (!(ft_strcmp("$?", name)))
		str = ft_itoa(g_gl.status_exit);
	else if (!(ft_strcmp("$0", name)))
		str = ft_strdup("minishell");
	else
		str = ft_strdup("");
	return (str);
}

static char	*find_name_in_envp(t_data *data, char *name, size_t i)
{
	char	*value;
	char	*key;
	char	**envp;

	value = NULL;
	envp = data->envp;
	key = ft_strjoin(name + 1, "=");
	while (key && envp[i])
	{
		if (!(ft_strncmp(key, envp[i], ft_strlen(key))))
		{
			value = ft_strdup(envp[i] + ft_strlen(key));
			ft_free_tmp(key);
			return (value);
		}
		i++;
	}
	if (!value)
		value = name_not_from_envp(name);
	ft_free_tmp(key);
	return (value);
}

static char	*find_name(char *str, size_t start, size_t end)
{
	char	*name;
	int		found;

	name = NULL;
	found = 0;
	while (!found)
	{
		if (str[end] == '?' || str[end] == '$' || ft_isdigit(str[end]))
		{
			end++;
			found = 1;
		}
		while (!found && (str[end] == '_' || ft_isalnum(str[end])))
			end++;
		found = 1;
	}
	name = ft_substr(str, start, end - start);
	return (name);
}

char	*open_dollar(t_data *data, char *str, size_t *i)
{
	char	*tmp;
	char	*name;
	char	*tmp_search;
	char	*tmp_befor;
	char	*tmp_after;

	tmp = str;
	tmp_befor = ft_befor_search(str, *i);
	name = find_name(str, *i, *i + 1);
	tmp_after = ft_after_search(str, ft_strlen(tmp_befor) + ft_strlen(name));
	if (ft_error_malloc(tmp_befor, name, tmp_after))
		return (clear_tmp(str, tmp_befor, name, tmp_after));
	tmp_search = find_name_in_envp(data, name, 0);
	if (ft_error_malloc(tmp_befor, tmp_search, tmp_after))
	{
		ft_free_tmp(name);
		return (clear_tmp(tmp, tmp_befor, tmp_search, tmp_after));
	}
	str = open_done(tmp_befor, tmp_search, tmp_after, i);
	ft_free_tmp(name);
	clear_tmp(tmp, tmp_befor, tmp_search, tmp_after);
	return (str);
}

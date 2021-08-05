/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:23:52 by scanary           #+#    #+#             */
/*   Updated: 2021/07/26 18:39:11 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_tmp(char *tmp, char *tmp_befor, char *tmp_search, \
					char *tmp_after)
{
	ft_free_tmp(tmp);
	ft_free_tmp(tmp_befor);
	ft_free_tmp(tmp_search);
	ft_free_tmp(tmp_after);
	return (NULL);
}

int	ft_error_malloc(char *tmp_befor, char *tmp_search, char *tmp_after)
{
	if (!tmp_befor || !tmp_search || !tmp_after)
		return (1);
	return (0);
}

char	*open_done(char *tmp_befor, char *tmp_search, char *tmp_after, \
					size_t *i)
{
	char	*tmp;
	char	*tmp_free;

	tmp = NULL;
	tmp = ft_strjoin(tmp_befor, tmp_search);
	if (tmp == NULL)
		return (NULL);
	tmp_free = tmp;
	*i = ft_strlen(tmp);
	tmp = ft_strjoin(tmp, tmp_after);
	ft_free_tmp(tmp_free);
	return (tmp);
}

char	*ft_befor_search(char *tmp, size_t start)
{
	char	*tmp_befor;

	tmp_befor = NULL;
	tmp_befor = ft_substr(tmp, 0, start);
	if (tmp_befor == NULL)
		return (NULL);
	return (tmp_befor);
}

char	*ft_after_search(char *tmp, size_t start)
{
	char	*tmp_after;

	tmp_after = NULL;
	tmp_after = ft_substr(tmp, start, ft_strlen(tmp) - start);
	if (tmp_after == NULL)
		return (NULL);
	return (tmp_after);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:17:34 by scanary           #+#    #+#             */
/*   Updated: 2021/07/28 17:01:47 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_need_arg(char *str, char *token)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	g_gl.status_exit = 258;
	return (1);
}

static int	shell_error(char *str, char *token)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("\'", 2);
	g_gl.status_exit = 258;
	return (1);
}

static int	bad_content_pipe(t_list *tmp)
{
	if (tmp)
	{
		if (tmp->next && !ft_strcmp("|", tmp->next->content))
			return (shell_error(ERR_2, tmp->next->content));
		if (!ft_strcmp("|", tmp->content) && tmp->next == NULL)
			return (shell_need_arg(ERR_3, "syntax error"));
	}
	return (0);
}

static int	bad_content_redir(t_list *tmp)
{
	if (tmp->next == NULL)
		return (shell_error(ERR_2, "newline"));
	if (!ft_strcmp("<", tmp->next->content) || \
	!ft_strcmp("<<", tmp->next->content) || \
	!ft_strcmp(">", tmp->next->content) || \
	!ft_strcmp(">>", tmp->next->content))
		return (shell_error(ERR_2, tmp->next->content));
	return (0);
}

int	sintax_error(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	if (ft_strchr(tmp->content, '.') && tmp->next == NULL)
		if (check_point(tmp->content))
			return (1);
	if (!ft_strcmp("|", tmp->content))
		return (shell_error(ERR_2, tmp->content));
	while (tmp)
	{
		if (!ft_strcmp("<", tmp->content) || \
		!ft_strcmp("<<", tmp->content) || !ft_strcmp(">", tmp->content) || \
		!ft_strcmp(">>", tmp->content))
		{
			if (bad_content_redir(tmp))
				return (1);
		}
		tmp = tmp->next;
		if (tmp && !ft_strcmp("|", tmp->content) && bad_content_pipe(tmp))
			return (1);
	}
	return (0);
}

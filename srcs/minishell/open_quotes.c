/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 06:41:11 by scanary           #+#    #+#             */
/*   Updated: 2021/07/26 18:36:20 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*open_quotes(t_data *data, char *content)
{
	size_t	i;

	i = 0;
	while (content[i] != '\0')
	{
		while (content && content[i] == '$')
			content = open_dollar(data, content, &i);
		while (content && content[i] == '\'')
			content = open_one_quotes(content, &i, i + 1);
		while (content && content[i] == '\"')
			content = open_double_quotes(data, content, &i, i + 1);
		if (content && content[i] != '$' && content[i] != '\'' && \
		content[i] != '\"' && content[i] != '\0')
			i++;
		if (content == NULL)
			break ;
	}
	return (content);
}

static int	parser_content_redirects(t_data *data, t_redirects *redir)
{
	if (redir && redir->content)
	{
		while (redir)
		{
			if (redir->content && (ft_strchr(redir->content, '$') || \
			ft_strchr(redir->content, '\"') || \
			ft_strchr(redir->content, '\'')))
			{
				redir->content = open_quotes(data, redir->content);
				if (redir->content == NULL)
					return (1);
			}
			redir = redir->next;
		}
	}
	return (0);
}

static int	parser_arguments_command(t_data *data, char **cmd_arr, size_t i)
{
	if (*cmd_arr)
	{
		while (i)
		{
			cmd_arr[i] = open_quotes(data, cmd_arr[i]);
			if (cmd_arr[i] == NULL)
				return (1);
			i--;
		}
		cmd_arr[i] = open_quotes(data, cmd_arr[i]);
		if (cmd_arr[i] == NULL)
			return (1);
	}
	return (0);
}

int	parser_quotes_and_dollar(t_data *data, t_commands *commands)
{
	t_commands	*tmp_cmd;

	tmp_cmd = commands;
	if (parser_arguments_command(data, tmp_cmd->cmd_arr, \
	tmp_cmd->count_args_for_cmd))
		return (1);
	if (parser_content_redirects(data, tmp_cmd->redir))
		return (1);
	if (tmp_cmd->pipe)
		parser_quotes_and_dollar(data, tmp_cmd->pipe);
	return (0);
}

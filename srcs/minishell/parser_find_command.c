/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:12:44 by scanary           #+#    #+#             */
/*   Updated: 2021/07/28 16:45:20 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*init_tmp(t_list *tokens, t_list *tmp_cmd)
{
	t_list	*tmp;

	tmp = NULL;
	if (tmp_cmd == NULL)
		tmp = tokens;
	else
		tmp = tmp_cmd;
	return (tmp);
}

static int	create_redirects(t_commands *cmds, t_list **tmp)
{
	if (*tmp)
	{
		if (!(ft_strcmp("<", (*tmp)->content)) || \
		!(ft_strcmp(">", (*tmp)->content)) || \
		!(ft_strcmp("<<", (*tmp)->content)) || \
		!(ft_strcmp(">>", (*tmp)->content)))
		{
			cmds->next_token_redir = 1;
			cmds->redir = find_all_redir(tmp);
			if (cmds->redir == NULL)
				return (1);
		}
	}
	return (0);
}

static int	create_cmd_args(t_commands *cmds, t_list **tmp, size_t *i)
{
	if (*tmp && (ft_strcmp("|", (*tmp)->content)))
	{
		cmds->cmd_arr[*i] = ft_strdup((*tmp)->content);
		if (cmds->cmd_arr[*i] == NULL)
			return (1);
		cmds->count_args_for_cmd++;
		*tmp = (*tmp)->next;
		++*i;
	}
	return (0);
}

static int	create_pipes(t_commands *cmds, t_list **tmp, size_t i)
{
	if (*tmp)
	{
		cmds->cmd_arr[i] = NULL;
		cmds->next_token_pipe = 1;
		cmds->pipe = init_struct_commands();
		if (cmds->pipe == NULL)
			return (1);
		*tmp = (*tmp)->next;
	}
	return (0);
}

int	find_command(t_data *data, t_commands *cmds, t_list *tokens, \
				t_list *tmp_cmd)
{
	t_list	*tmp;
	size_t	i;

	tmp = init_tmp(tokens, tmp_cmd);
	cmds->cmd_arr = (char **)malloc(sizeof(char *) * (ft_lstsize(tmp) + 1));
	if (cmds->cmd_arr == NULL)
		return (1);
	i = 0;
	while (tmp)
	{
		if (!(ft_strcmp("|", tmp->content)))
		{
			if (create_pipes(cmds, &tmp, i))
				return (1);
			find_command(data, cmds->pipe, tokens, tmp);
			return (0);
		}
		if (create_redirects(cmds, &tmp))
			return (1);
		if (create_cmd_args(cmds, &tmp, &i))
			return (1);
	}
	cmds->cmd_arr[i] = NULL;
	return (0);
}

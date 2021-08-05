/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:02:26 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 18:20:14 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(t_data *data, size_t *start_token, size_t *i, \
						t_list **tokens)
{
	size_t	start;
	size_t	end;

	start = *start_token;
	end = *i - *start_token;
	is_token(data, start, end, tokens);
	while (data->input[*i] == ' ')
		(*i)++;
	*start_token = *i;
	return (1);
}

void	quotes(t_data *data, size_t *i)
{
	if (data->input[*i] == '\'')
	{
		(*i)++;
		while (data->input[*i] != '\'')
			(*i)++;
	}
	else if (data->input[*i] == '\"')
	{
		(*i)++;
		while (data->input[*i] != '\"')
			(*i)++;
	}
	(*i)++;
}

static void	find_start_token(t_data *data, size_t *start_token, size_t *i, \
						t_list **token)
{
	int		key;

	key = 0;
	if (data->input[*i] == '|')
		key = is_pipe(data, start_token, i, token);
	if (data->input[*i] == '>' || data->input[*i] == '<')
		key = is_redir(data, start_token, i, token);
	if (data->input[*i] == ' ')
		key = is_space(data, start_token, i, token);
	if (data->input[*i] == '\'' || data->input[*i] == '\"')
		key = is_quotes(data, start_token, i, token);
	if (key == 0)
		(*i)++;
}

static void	find_token(t_data *data, t_list **token)
{
	size_t	i;
	size_t	start_token;

	i = 0;
	start_token = 0;
	*token = NULL;
	while (data->input[i] != '\0')
		find_start_token(data, &start_token, &i, token);
	if (data->input[start_token] != '\0')
		is_token(data, start_token, ft_strlen(data->input), token);
}

t_list	*split_by_tokens(t_data *data)
{
	t_list	*new_tokens;

	find_token(data, &new_tokens);
	return (new_tokens);
}

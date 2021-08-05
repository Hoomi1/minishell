/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:50:48 by scanary           #+#    #+#             */
/*   Updated: 2021/07/27 16:52:27 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(t_data *data, size_t *start_token, size_t *i, \
						t_list **tokens)
{
	size_t	start;
	size_t	end;

	start = *start_token;
	end = 0;
	while (data->input[*i] != '\0' && end == 0)
	{
		quotes(data, i);
		if (data->input[*i] == ' ' || data->input[*i] == '\0')
			end = *i - *start_token;
	}
	is_token(data, start, end, tokens);
	while (data->input[*i] == ' ')
		(*i)++;
	*start_token = *i;
	return (1);
}

int	is_pipe(t_data *data, size_t *start_token, size_t *i, \
						t_list **tokens)
{
	size_t	start;
	size_t	end;

	start = *start_token;
	end = *i - *start_token;
	if (end)
		is_token(data, start, end, tokens);
	start = *i;
	(*i)++;
	end = 1;
	is_token(data, start, end, tokens);
	while (data->input[*i] == ' ')
		(*i)++;
	*start_token = *i;
	return (1);
}

int	is_redir(t_data *data, size_t *start_token, size_t *i, \
						t_list **tokens)
{
	size_t	start;
	size_t	end;

	start = *start_token;
	end = *i - *start_token;
	if (end)
		is_token(data, start, end, tokens);
	start = *i;
	if ((data->input[start] == '<' && data->input[start + 1] == '<') || \
	(data->input[start] == '>' && data->input[start + 1] == '>'))
	{
		(*i) = start + 2;
		end = 2;
	}
	else
	{
		(*i)++;
		end = 1;
	}
	is_token(data, start, end, tokens);
	while (data->input[*i] == ' ')
		(*i)++;
	*start_token = *i;
	return (1);
}

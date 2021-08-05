/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 23:52:24 by scanary           #+#    #+#             */
/*   Updated: 2021/04/10 02:19:49 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_cln(char **src)
{
	free(*src);
	*src = NULL;
}

static int	ft_error(char *track, char *buf)
{
	if (NULL != track)
		ft_cln(&track);
	if (NULL != buf)
		ft_cln(&buf);
	return (-1);
}

static int	get_track(char **track, char *buf)
{
	char		*leak;

	if (*track)
	{
		leak = *track;
		*track = ft_strjoin(*track, buf);
		if (!(*track))
			return (ft_error(*track, buf));
		ft_cln(&leak);
	}
	else
	{
		*track = ft_strdup(buf);
		if (!(*track))
			return (ft_error(*track, buf));
	}
	return (0);
}

static int	check_track(char *track, char **line)
{
	char		*is_enter;

	if (!(track))
		*line = ft_strdup("");
	if (track)
	{
		is_enter = ft_strchr(track, '\n');
		if ((is_enter))
		{
			*is_enter = '\0';
			is_enter++;
			*line = ft_strdup(track);
			ft_memcpy(track, is_enter, ft_strlen(is_enter) + 1);
			return (1);
		}
		else
		{
			*line = ft_strdup(track);
			ft_cln(&track);
		}
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*track;
	char		*buf;
	int			size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(buf))
		return (ft_error(track, buf));
	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (ft_error(track, buf));
	size = 1;
	while (!ft_strchr(track, '\n') && (size))
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (ft_error(track, buf));
		buf[size] = '\0';
		if ((get_track(&track, buf)) == -1)
			return (-1);
	}
	ft_cln(&buf);
	size = check_track(track, line);
	if (!(*line))
		return (-1);
	return (size);
}

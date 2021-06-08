/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:14:47 by cyuuki            #+#    #+#             */
/*   Updated: 2021/06/08 19:22:08 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "libft/libft.h"
#include <term.h>

#define BUFFER_SIZE 1024

struct termios saved_attributes;

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

char	*copy_sim(char *buffer_str, char *buffer)
{
	int i;

	i = 0;
	while(i < ft_strlen(buffer))
	{
		buffer_str[i] = buffer[i];
		i++;
	}
	return (buffer_str);
}

void	keyhuck(char *buffer)
{
	char *buffer_str;

	if(!ft_strncmp(buffer, "\e[C", 3))
	{
		if(!ft_strncmp(buffer + 1, "\0", 1))
			tputs(cursor_right, 1, ft_putchar);
	}
	else if(!ft_strncmp(buffer, "\e[D", 3))
	{
		tputs(cursor_left, 1, ft_putchar);
	}
	else if(!ft_strncmp(buffer, "\e[A", 3))
	{
		tputs(clr_bol, 1, ft_putchar);
		tputs(clr_eol, 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		write(1, "minishell->", 11);
		tputs(tgetstr("co", &buffer), 1, ft_putchar);
		write(1, "up", 2);
	}
	else if(!ft_strncmp(buffer, "\e[B", 3))
	{
		tputs(clr_bol, 1, ft_putchar);
		tputs(clr_eol, 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		write(1, "minishell->", 11);
		tputs(tgetstr("co", &buffer), 1, ft_putchar);
		write(1, "down", 4);
	}
	else if(!ft_strncmp(buffer, "\x7f", 1))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
}

int	read_line(int gc, char *gv, char *nv)
{
	char *buffer;
	int count;
	char *buffer_key;

	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!BUFFER_SIZE)
		return (-1);
	tcgetattr(0, &saved_attributes);
	saved_attributes.c_lflag &= ~(ECHO);
	saved_attributes.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &saved_attributes);
	count = tgetent(0, "xterm-256color");
	if(count < 0)
		return (-1);
	buffer_key = buffer;
	tputs(tgetstr("sc", &buffer_key), 1, ft_putchar);
	write(1, "minishell->", 11);
	while(ft_strncmp(buffer, "\4", 1))
	{	
		count = read(0, buffer, BUFFER_SIZE);
		if (count < 0)
			return (-1);
		write(1, buffer, 1);
		if(ft_strncmp(buffer, "\n", 1) == 0)
		{
			buffer_key = buffer;
			tputs(tgetstr("sc", &buffer_key), 1, ft_putchar);
			write(1, "minishell->", 11);
		}
		keyhuck(buffer);
	}
	return (0);
}

int	main(int gc, char **gv, char **nv)
{
	read_line(gc, *gv, *nv);
	tcgetattr(0, &saved_attributes);
	saved_attributes.c_lflag |= ECHO;
	saved_attributes.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &saved_attributes);
	return (0);
}
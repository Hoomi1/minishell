/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:14:47 by cyuuki            #+#    #+#             */
/*   Updated: 2021/06/07 17:28:58 by cyuuki           ###   ########.fr       */
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

void keyhuck(char *buffer)
{
	if(!ft_strncmp(buffer, "\e[C", 3))
	{
		tputs(buffer, 1, putchar);
	}
	if(!ft_strncmp(buffer, "\e[D", 3))
	{
		write(1, "left", 4);
		write(1, "left", 4);
	}
	if(!ft_strncmp(buffer, "\e[A", 3))
	{
		write(1, "up", 2);
	}
	if(!ft_strncmp(buffer, "\e[B", 3))
	{
		write(1, "down", 4);
	}
}

int	read_line(int gc, char *gv, char *nv)
{
	char *buffer;
	int count;
	
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
	while(1)
	{
		count = read(0, buffer, BUFFER_SIZE);
		if (count < 0)
			return (-1);
		write(1, buffer, 1);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:14:47 by cyuuki            #+#    #+#             */
/*   Updated: 2021/06/14 20:13:38 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios saved_attributes;

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

// char *ft_strncpy (char *dest, const char *src, size_t n)
// {
// 	static int i;
	
// 	while(src[i] && i <= n)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	while(i <= n)
// 	{
// 		dest[i++] = '\0';
// 	}
// 	return (dest);
// }

// void	*ft_realloc (void *ptr, size_t size)
// {
// 	char *str;
// 	char *ptr_str;

// 	ptr_str =(char *)ptr;
// 	if( ptr && ft_strlen(ptr_str) <= size)
// 	{
// 		str = malloc(size);
// 	}
// 	str[size] = '\0';
// 	//free(ptr);
// 	return (str);
// }

t_listtwo *list_next(char *strh)
{
	t_listtwo *newlist;

	newlist = (t_listtwo *)malloc(sizeof(t_listtwo));
	newlist->next = NULL;
	newlist->prev = NULL;
	newlist->str = strh;
	if (head == NULL)
		head = tail = newlist;
	else
	{
		tail->next = newlist;
		newlist->prev = tail;
		tail = newlist;
	}

	return(head);
}

void clear_buffer(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		str[i] = 0;
		i++;
	}
}

int	str_alfa(char *buffer)
{
	int i;

	i = 0;
	// if(ft_isalpha(buffer[i]) == 1 || ft_isdigit(buffer[i]) == 1 || buffer[i] == '\n')
	if(ft_isprint(buffer[i]) == 1 || buffer[i] == '\n')
		return (0);
	return (-1);
}

void my_history(t_str *str)
{
	int i;

	i = 0;
	if(str->fd == 0)
		str->fd = open("temp_history", O_WRONLY | O_CREAT | O_TRUNC);
	if(str->fd > -1)
	{
		write(str->fd, str->buffer_str, ft_strlen(str->buffer_str));
	}
	list_next(str->buffer_str);
	while (head != NULL)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}

void	keyhuck(char *buffer, t_str *str)
{
	if(str_alfa(buffer) == 0)
	{
		str->buffer_str = ft_strjoin(str->buffer_str, buffer);
		str->i = ft_strlen(str->buffer_str);
		free(str->buffer_str);
	}
	if(!ft_strncmp(buffer, "\e[C", 3) && str->i + 1<= ft_strlen(str->buffer_str))
	{
		tputs(cursor_right, 1, ft_putchar);
		str->i++;
	}
	else if(!ft_strncmp(buffer, "\e[D", 3) && str->i >= 0)
	{
			tputs(cursor_left, 1, ft_putchar);
			str->i--;
	}
	else if(!ft_strncmp(buffer, "\e[A", 3))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eol, 1, ft_putchar);
		tputs(tgetstr("co", &buffer), 1, ft_putchar);
		write(1, "up", 4);
	}
	else if(!ft_strncmp(buffer, "\e[B", 3))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eol, 1, ft_putchar);
		tputs(tgetstr("co", &buffer), 1, ft_putchar);
		write(1, "down", 4);
		
	}
	else if(!ft_strncmp(buffer, "\x7f", 1))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	if(ft_strchr(str->buffer_str, '\n') != NULL)
	{
		my_history(str);
		str->buffer_str = "";
	}
}

int	read_line(int gc, char *gv, char *nv)
{
	char *buffer;
	int count;
	t_str str;

	str.i = 0;
	str.fd = 0;
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
	write(1, "minishell->", 11);
	tputs(save_cursor, 1, ft_putchar);
	str.buffer_str = "";
	while(ft_strncmp(buffer, "\4", 1))
	{	
		clear_buffer(buffer);
		count = read(0, buffer, BUFFER_SIZE);
		write(1, buffer, 1);
		if(ft_strncmp(buffer, "\n", 1) == 0)
		{
			write(1, "minishell->", 11);
			tputs(save_cursor, 1, ft_putchar);
		}
		keyhuck(buffer, &str);
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
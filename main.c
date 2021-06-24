/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:14:47 by cyuuki            #+#    #+#             */
/*   Updated: 2021/06/24 18:51:45 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct termios saved_attributes;



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
	char *str;

	str = strh;
	newlist = (t_listtwo *)malloc(sizeof(t_listtwo));
	newlist->next = NULL;
	newlist->prev = NULL;
	newlist->str = str;
	if (head == NULL)
	{
		head = newlist;
		tail = newlist;
	}
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
	if(ft_isprint(buffer[i]) == 1 || buffer[i] == '\n')
		return (0);
	return (-1);
}

void	my_history(t_str *str)
{
	if (str->fd == 0)
		str->fd = open("temp_history", O_WRONLY | O_CREAT | O_TRUNC);
	if(gl.signal == 1)
		str->buffer_str = "\n";
	if ((str->fd > -1 && *str->buffer_str != '\n') )
	{
		write(str->fd, str->buffer_str, ft_strlen(str->buffer_str));
	}
	list_next(str->buffer_str);
}

void	keyhuck_str(char *buffer, t_str *str)
{
		str->buffer_str = ft_strjoin(str->buffer_str, buffer);
		str->i = ft_strlen(str->buffer_str);
		free(str->buffer_str);
		str->lef_rig = str->lef_rig + 1;
		if(str->lef_rig != str->i)
			str->i = str->lef_rig;
		if (str->del > 0)
			str->del = str->del - 1;
}

void my_pwd(char *str)
{
	char dir[1024];
	char *pwd = "pwd\n";
	
	if (ft_strncmp(pwd, str, ft_strlen(str)) == 0 && ft_strlen(str) != 0)
	{
		if (getcwd(dir, 1024) != NULL)
			printf("%s\n", dir);
		str = "\0";
	}
}

void my_cd(t_str *str)
{
	char *str_cd;

	if(str->buffer_str[0] == 'c' && str->buffer_str[1] == 'd')
	{
		str_cd = ft_strrchr(str->buffer_str, ' ');
		str_cd++;
		if (*str_cd == '.' && *(str_cd + 1) == '.')
		{
			printf("Hello");
		}
		if (chdir(str_cd) == 0)
		{
			
		}
		else
		{
			printf("bash: cd: %s: No such file or directory\n", str_cd);
		}
	}
}

void	my_builtins(t_str *str)
{
	char *str_built;
	
	str_built = ft_strchr(str->buffer_str, ' ');
	str_built++;
	//printf("%s\n", str_built);
	my_pwd(str->buffer_str);
	my_cd(str);
}

void key_history(t_str *str)
{
	my_history(str);
	//my_builtins(str);
	str->buffer_str = "";
	str->i = 0;
	str->lef_rig = 0;
	str->del = 0;
	gl.signal = 0;
}

void keyhuck_down(char *buffer)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	tputs(tgetstr("co", &buffer), 1, ft_putchar);
	write(1, head->str, ft_strlen(head->str));
	if(head->prev != NULL)
		head = head->prev;
}

void keyhuck_up(char *buffer)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	tputs(tgetstr("co", &buffer), 1, ft_putchar);
	write(1, head->str , ft_strlen(head->str));
	if (head->next != NULL)
		head = head->next;
}

void keyhuck_del(t_str *str)
{
	tputs(cursor_left, 1, ft_putchar);
	tputs(delete_character, 1, ft_putchar);
	str->lef_rig--;
	str->del = 1;
	// if (str->lef_rig != str->i)
	// 	str->buffer_str[str->lef_rig + str->del] = '\0';
	// else
	str->buffer_str[str->i - str->del] = '\0';
	str->i--;
}

void my_init()
{
	printf("\n");
	write(1, "minishell->", 11);
	tputs(save_cursor, 1, ft_putchar);
	gl.signal = 1;
}

void my_quit()
{
	
}

void signal_my(char *buffer)
{
	void (*funcptr)(int);
	signal(SIGINT, my_init);
	signal(SIGQUIT,my_quit);
}

void	keyhuck(char *buffer, t_str *str, int count)
{	
	if(str_alfa(buffer) == 0)
	{
		keyhuck_str(buffer, str);
	}
	signal_my(buffer);
	if(ft_strchr(str->buffer_str, '\n') != NULL || gl.signal == 1)
	{
		key_history(str);
	}
	if(!ft_strncmp(buffer, "\e[C", 3) && str->lef_rig < str->i)
	{
		tputs(cursor_right, 1, ft_putchar); // right
		str->lef_rig++;
	}
	else if(!ft_strncmp(buffer, "\e[D", 3) && str->lef_rig != 0)
	{
		tputs(cursor_left, 1, ft_putchar); // left
		str->lef_rig--;
	}
	else if(!ft_strncmp(buffer, "\e[A", 3) && head != NULL)
	{
		keyhuck_up(buffer);
	}
	else if(!ft_strncmp(buffer, "\e[B", 3) && head != NULL)
	{
		keyhuck_down(buffer);
	}
	else if(!ft_strncmp(buffer, "\x7f", 1) && str->lef_rig != 0)
	{
		keyhuck_del(str);
	}
}

void settin_par(t_str *str)
{
	str->i = 0;
	str->fd = 0;
	str->lef_rig = 0;
	str->del = 0;
	str->buffer_str = "";
}

int settin_term()
{
	int count;
	
	tcgetattr(0, &gl.saved_attributes);
	gl.saved_attributes.c_lflag &= ~(ECHO);
	gl.saved_attributes.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &gl.saved_attributes);
	count = tgetent(0, "xterm-256color");
	if(count < 0)
		return (-1);
	return (count);
}

void infin_while(char *buffer, t_str *str, int count)
{
	while(1)
	{	
		clear_buffer(buffer);
		count = read(0, buffer, BUFFER_SIZE);
		if(count == 1)
			write(1, buffer, 1);
		if(ft_strncmp(buffer, "\n", 1) == 0)
		{
			my_builtins(str);
			write(1, "minishell->", 11);
			tputs(save_cursor, 1, ft_putchar);
		}
		keyhuck(buffer, str, count);
		if (!ft_strncmp(buffer, "\4", 1) && !ft_strncmp(str->buffer_str, "", 1))
		{	
			write(1, "exit", 4);
			break ;
		}
	}
}

int	read_line(int gc, char *gv, char *nv)
{
	char *buffer;
	int count;
	t_str str;
	
	settin_par(&str);
	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!BUFFER_SIZE)
		return (-1);
	count = settin_term();
	write(1, "minishell->", 11);
	tputs(save_cursor, 1, ft_putchar);
	infin_while(buffer, &str, count);
	// while(head != NULL)
	// {
	// 	printf("%s\n", head->str);
	// 	head = head->next;
	// }
	return (0);
}

int	main(int gc, char **gv, char **nv)
{
	gl.nv = *nv;
	gl.gv = *gv;
	read_line(gc, *gv, *nv);
	tcgetattr(0, &gl.saved_attributes);
	gl.saved_attributes.c_lflag |= ECHO;
	gl.saved_attributes.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &gl.saved_attributes);
	return (0);
}
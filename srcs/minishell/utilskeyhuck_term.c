/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilskeyhuck_term.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:48:37 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/27 21:24:51 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	key_huckclear(char *buffer, t_str *str)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (ft_strlen(str->buffer_str) >= w.ws_col)
	{
		tputs(restore_cursor, 1, ft_putchar);
		i = ft_strlen(str->buffer_str);
		while (i >= 0)
		{
			tputs(cursor_down, 1, ft_putchar);
			tputs(clr_eol, 1, ft_putchar);
			i = i - w.ws_col;
		}
		tputs(restore_cursor, 1, ft_putchar);
	}
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	tputs(tgetstr("co", &buffer), 1, ft_putchar);
}

void	keyhuck_down(char *buffer, t_str *str)
{
	key_huckclear(buffer, str);
	if (g_gl.head->next != NULL)
	{
		if (g_gl.size_i == 0)
			g_gl.head = g_gl.head->next;
		if (g_gl.size_i == 1)
		{
			g_gl.head = g_gl.head->next;
			g_gl.size_i = 0;
		}
		write(1, g_gl.head->str, ft_strlen(g_gl.head->str));
		str->buffer_str = g_gl.head->str;
		str->i = ft_strlen(g_gl.head->str);
		str->lef_rig = str->i;
		g_gl.size_i = 0;
	}
	else if (g_gl.head->next == NULL)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eol, 1, ft_putchar);
		str->buffer_str = "";
	}
}

void	keyhuck_up(char *buffer, t_str *str)
{
	key_huckclear(buffer, str);
	if (g_gl.head->prev != NULL)
	{
		if (g_gl.size_i == 1)
			g_gl.head = g_gl.head->prev;
		if (g_gl.size_i == 0)
		{
			g_gl.head = g_gl.head->prev;
			g_gl.size_i = 1;
		}
		write(1, g_gl.head->str, ft_strlen(g_gl.head->str));
		str->buffer_str = g_gl.head->str;
		str->i = ft_strlen(g_gl.head->str);
		str->lef_rig = str->i;
		g_gl.size_i = 1;
	}
	else if (g_gl.head->prev == NULL)
	{
		write(1, g_gl.head->str, ft_strlen(g_gl.head->str));
		str->buffer_str = g_gl.head->str;
		str->i = ft_strlen(g_gl.head->str);
		str->lef_rig = str->i;
	}
}

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	key_history(t_str *str, t_data *data)
{
	char	*tmp;

	tmp = str->buffer_str;
	my_history(str, data);
	sizetwo(g_gl.head);
	refactor(str->buffer_str);
	tcsetattr(0, TCSANOW, &g_gl.load_attributes);
	executor(data, str->buffer_str);
	tcsetattr(0, TCSANOW, &g_gl.saved_attributes);
	write(1, "minishell->", 11);
	tputs(save_cursor, 1, ft_putchar);
	str->buffer_str = "";
	str->i = 0;
	str->lef_rig = 0;
	str->del = 0;
	g_gl.signal = 0;
	while (g_gl.head && g_gl.head->next != NULL)
		g_gl.head = g_gl.head->next;
}

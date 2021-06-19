/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:45:37 by cyuuki            #+#    #+#             */
/*   Updated: 2021/06/14 19:53:36 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "libft/libft.h"
#include <term.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024

typedef struct s_list_two
{
	void				*content;
	struct s_list_two	*next;
	struct s_list_two	*prev;
	
} t_list_two;

typedef struct s_listtwo
{
	void *str;
	s_listtwo *next;
	s_listtwo *prev;

}	t_listtwo;

t_listtwo *head, *tail;

typedef struct s_str
{
	char *buffer_str;
	int i;
	int fd;
} t_str;


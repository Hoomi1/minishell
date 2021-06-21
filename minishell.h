/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:45:37 by cyuuki            #+#    #+#             */
/*   Updated: 2021/06/21 20:12:59 by cyuuki           ###   ########.fr       */
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

typedef struct s_listtwo
{
	void *str;
	struct s_listtwo *next;
	struct s_listtwo *prev;

}	t_listtwo;

t_listtwo *head, *tail;

typedef struct s_str
{
	char *buffer_str;
	int i;
	int fd;
	int lef_rig;
	int del;
} t_str;


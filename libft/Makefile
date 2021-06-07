# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 17:47:25 by cyuuki            #+#    #+#              #
#    Updated: 2021/04/28 16:49:46 by cyuuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wextra -Werror -Wall -c
HEADER = libft.h
OBJS = $(FUNCS:.c=.o)
FUNCS = ft_atoi.c ft_bzero.c ft_calloc.c  \
ft_memcpy.c ft_memset.c ft_strchr.c \
ft_strlen.c ft_strncmp.c ft_strrchr.c \
ft_strdup.c ft_strjoin.c \
ft_itoa.c \
ft_split.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstclear.c
BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(BONUS_OBJ) $(OBJS)
	$(CC) $(FLAGS) $(FUNCS) libft.h
	ar rc $(NAME) $(OBJS) $(BONUS_OBJ)

bonus: $(BONUS_OBJ)
	$(CC) $(FLAGS) $(BONUS) libft.h
	ar rc $(NAME) $(BONUS_OBJ)

clean:
	rm -f $(OBJS) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY:	clean	fclean	all	re

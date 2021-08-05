# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scanary <scanary@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 14:34:10 by scanary           #+#    #+#              #
#    Updated: 2021/07/04 02:05:05 by scanary          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
FLAG = -Wall -Wextra -Werror

FUNC = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c\
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_toupper.c ft_tolower.c\
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c\
		ft_split.c ft_itoa.c ft_strmapi.c

OBJ = $(FUNC:%.c=%.o)

HEADER = libft.h

FUNC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstfree.c\
				ft_lstiter.c ft_lstmap.c\
				ft_amount_digit.c ft_strcmp.c ft_strndup.c\
				ft_free_tmp.c ft_free_arr.c

OBJ_BONUS = $(FUNC_BONUS:%.c=%.o)

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

bonus: $(OBJ) $(OBJ_BONUS)
	@ar rc $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus $(NAME)
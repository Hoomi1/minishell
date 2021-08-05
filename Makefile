# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scanary <scanary@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 14:59:43 by scanary           #+#    #+#              #
#    Updated: 2021/07/28 19:30:05 by scanary          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = 	srcs/minishell/minishell.c \
		srcs/minishell/init_data.c \
		srcs/minishell/term.c \
		srcs/minishell/utils_term.c \
		srcs/minishell/utilstwo_term.c \
		srcs/minishell/utilsthree_term.c \
		srcs/minishell/utilshistory_term.c \
		srcs/minishell/utilskeyhuck_term.c \
		srcs/minishell/executor.c \
		srcs/minishell/parser.c \
		srcs/minishell/parser_commands.c \
		srcs/minishell/parser_find_command.c \
		srcs/minishell/tokens.c \
		srcs/minishell/tokens_utils.c \
		srcs/minishell/token_create.c \
		srcs/minishell/syntax_error.c \
		srcs/minishell/syntax_check_point.c \
		srcs/minishell/init_commands.c \
		srcs/minishell/open_quotes.c \
		srcs/minishell/open_quotes_utils.c \
		srcs/minishell/open_dollar.c \
		srcs/minishell/open_one_quotes.c \
		srcs/minishell/open_double_quotes.c \
		srcs/minishell/search_for_commands.c \
		srcs/minishell/execute_commands.c \
		srcs/minishell/execute_commands_utils.c \
		srcs/minishell/prosess_command.c \
		srcs/minishell/builtin_commands/cd.c \
		srcs/minishell/builtin_commands/env.c \
		srcs/minishell/builtin_commands/pwd.c \
		srcs/minishell/builtin_commands/exit.c \
		srcs/minishell/builtin_commands/exit_utils.c \
		srcs/minishell/builtin_commands/echo.c \
		srcs/minishell/builtin_commands/unset.c \
		srcs/minishell/builtin_commands/export.c \
		srcs/minishell/builtin_commands/export_writeobs.c \
		srcs/minishell/builtin_commands/export_utils.c \
		srcs/minishell/builtin_commands/export_utilstwo.c \
		srcs/minishell/program_exit.c \
		srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = srcs/libft/
LIBS = -L$(LIBFT_DIR) -lft -ltermcap
LIBFT = libft.a

all: $(NAME)
%.o: %.c srcs/minishell/minishell.h srcs/libft/libft.h
	@$(CC) $(FLAGS) -I$(LIBFT_DIR) -c $< -o $@
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)
$(LIBFT):
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)
	@cp $(LIBFT_DIR)/$(LIBFT) .
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(LIBFT)
re: fclean all

.PHONY: all clean fclean re

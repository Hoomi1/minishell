/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 23:00:36 by scanary           #+#    #+#             */
/*   Updated: 2021/07/28 17:14:58 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>

# define BUFFER_SIZE_MINI 1024
# define SHELL_NAME "minishell: "
# define ERR_1 "filename argument required\n.: usage: . filename [arguments]"
# define ERR_2 "syntax error near unexpected token "
# define ERR_3 "unexpected end of file"

typedef enum e_type_cmd
{
	CMD_CD = 1,
	CMD_ECHO,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXPORT,
	CMD_PWD,
	CMD_UNSET,
	CMD_IN_EXECVE,
	CMD_ERROR
}	t_type_cmd;

typedef enum e_type_redir
{
	REDIR_LEFT_1 = 1,
	REDIR_LEFT_2,
	REDIR_RIGHT_1,
	REDIR_RIGHT_2
}	t_type_redir;

typedef struct s_data
{
	char				*input;
	char				**envp;
	int					home_dir;
	int					current_pwd;
	int					old_pwd;
	int					env_var;
	int					path;
	int					count_str;
	int					fd0;
	int					fd1;
	t_list				*list_envp;
}	t_data;

typedef struct s_redirects
{
	int					type_redir;
	char				*content;
	struct s_redirects	*next;
}	t_redirects;

typedef struct s_commands
{
	char				*cmd;
	int					type_cmd;
	pid_t				pid;
	char				*cmd_dir;
	char				**cmd_arr;
	int					count_args_for_cmd;
	int					next_token_redir;
	int					next_token_pipe;
	struct s_redirects	*redir;
	struct s_commands	*pipe;
}	t_commands;

typedef struct s_listtwo
{
	void				*str;
	struct s_listtwo	*next;
	struct s_listtwo	*prev;

}	t_listtwo;

typedef struct s_listexp
{
	char				*name;
	char				*value;
}	t_listexp;

struct s_global			g_gl;

typedef struct s_global
{
	struct termios	saved_attributes;
	struct termios	load_attributes;
	struct winsize	win;
	struct stat		buf;
	int				signal;
	int				flag;
	t_listtwo		*head;
	t_listtwo		*tail;
	int				size_i;
	int				flag_cat;
	int				status_exit;
}	t_global;

typedef struct s_history
{
	char				*str_list;
	char				*file;
	char				*pwd;
	char				*buffer_list;
}	t_history;

typedef struct s_str
{
	char				*buffer_str;
	int					i;
	int					fd;
	int					lef_rig;
	int					del;
}	t_str;

t_data		*init_data(int argc, char **argv, char **envp);
void		parse_env_in_data(t_data *data);
int			term(t_data *data);
void		executor(t_data *data, char *str);

t_list		*split_by_tokens(t_data *data);
int			is_quotes(t_data *data, size_t *start_token, size_t *i, \
			t_list **tokens);
void		quotes(t_data *data, size_t *i);
int			is_pipe(t_data *data, size_t *start_token, size_t *i, \
			t_list **tokens);
int			is_redir(t_data *data, size_t *start_token, size_t *i, \
			t_list **tokens);
void		is_token(t_data *data, size_t start, size_t end, t_list **tokens);
int			sintax_error(t_list *tokens);
int			check_point(char *str);

t_commands	*parser(t_data *data);
void		parser_command_test(t_data *data, t_commands *commands, \
			t_list *tokens);
int			find_command(t_data *data, t_commands *cmds, \
			t_list *tokens, t_list *tmp_cmd);
void		full_info_command(t_data *data, t_commands *commands);
t_redirects	*find_all_redir(t_list **tokens);
int			find_redirect(t_list **tokens, t_redirects *redir);
void		search_for_commands(t_commands *commands, t_data *data);

t_commands	*init_struct_commands(void);
t_redirects	*init_struct_redir(void);
void		init_fd_command(int *fd, int *fd_redir_write, int *fd_redir_read);

int			get_heredoc(char *stop_work);
void		redirect_end(t_commands *cmd, int *fd_redir_write, \
						int *fd_redir_read);
void		completion_cmd_line(t_data *data, t_commands *commands);

int			parser_quotes_and_dollar(t_data *data, t_commands *commands);
char		*ft_befor_search(char *tmp, size_t start);
char		*ft_after_search(char *tmp, size_t start);
char		*open_dollar(t_data *data, char *str, size_t *i);
char		*open_one_quotes(char *str, size_t *i, size_t end);
char		*open_double_quotes(t_data *data, char *str, size_t *i, size_t end);
int			ft_error_malloc(char *tmp_befor, char *tmp_search, char *tmp_after);
char		*clear_tmp(char *tmp, char *tmp_befor, char *tmp_search, \
			char *tmp_after);
char		*open_done(char *tmp_befor, char *tmp_search, char *tmp_after, \
			size_t *i);

void		init_command_dir(t_commands *commands, t_data *data, \
			char **split_path, char *dir_path);
void		execute_commands(t_data *data, t_commands *commands);
void		execute_cmd_line(t_data *data, t_commands *commands);
void		prosess_command(t_data *data, t_commands *commands);
void		ft_pwd(t_data *data, t_commands *commands);
void		ft_cd(t_data *data, t_commands *commands);
void		ft_echo(t_commands *commands);
void		ft_export(t_commands *commands, t_data *data);
void		write_obser(char *name, t_commands *commands, int i);
t_listexp	*add_str(int i, t_data *data);
char		*lnew_value(t_list *list);
char		*lnew_name(t_list *list);
char		*equals_arr(char *name, char *value);
char		**is_listarr(t_list *list);
int			argum(char *name, char *value, t_list **list);
int			cheak_value(char *name, char *value, t_list **list);
char		*getvalue(char *arr);
int			check_name(char *str);
char		*getname(char *arr);
int			renamenode(t_list	*new_list, char *name, char *value);
int			ft_unset(t_commands *commands, t_data *data);
void		ft_env(t_commands *commands, t_data *data);
void		ft_exit(t_commands *commands, t_data *data);
void		succes_exit(t_data *data, t_commands *commands, int exit);
void		prover_exit(t_commands *commands, int *fl_exit, int i);
int			ft_putchar(int c);
void		settin_par(t_str *str);
int			settin_term(void);
void		histdupview(char *file, t_str *str);
void		refactor(char *buffer_str);
t_listtwo	*list_next(char *strh);
void		clear_buffer(char *str);
void		clear_buffer(char *str);
void		keyhuck_str(char *buffer, t_str *str);
int			str_alfa(char *buffer);
int			sizetwo(t_listtwo *lst);
void		write_list(char *str_list);
int			my_history(t_str *str, t_data *data);
void		bufadd(t_str *str, t_history *histor);
void		signal_my(void);
void		keyhuck_up(char *buffer, t_str *str);
void		keyhuck_down(char *buffer, t_str *str);
void		key_history(t_str *str, t_data *data);
void		freeing_memory_data(t_data *data);
void		freeing_memory_commands(t_commands *commands);
void		freeing_memory_redirects(t_redirects *redir);
void		freelist(void *exp);
int			shell_exit(t_data *data, t_commands *commands, char *str, int num);

#endif

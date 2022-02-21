#include "minishell.h"

static int	define_type_redir(char *redir)
{
	if (ft_strlen(redir) == 1 && ft_strchr(redir, '<'))
		return (REDIR_LEFT_1);
	else if (ft_strlen(redir) == 2 && !(ft_strcmp("<<", redir)))
		return (REDIR_LEFT_2);
	else if (ft_strlen(redir) == 1 && !(ft_strcmp(">", redir)))
		return (REDIR_RIGHT_1);
	else if (ft_strlen(redir) == 2 && !(ft_strcmp(">>", redir)))
		return (REDIR_RIGHT_2);
	return (0);
}

int	find_redirect(t_list **tokens, t_redirects *redir)
{
	t_list	*tmp;

	tmp = *tokens;
	redir->type_redir = define_type_redir(tmp->content);
	tmp = tmp->next;
	if (tmp && (ft_strcmp("|", tmp->content)))
	{
		redir->content = ft_strdup(tmp->content);
		if (redir->content == NULL)
			return (-1);
		tmp = tmp->next;
	}
	if (tmp)
	{
		*tokens = tmp;
		if (!(ft_strcmp("<", tmp->content)) || \
		!(ft_strcmp(">", tmp->content)) || !(ft_strcmp("<<", tmp->content)) || \
		!(ft_strcmp(">>", tmp->content)))
			redir->next = find_all_redir(tokens);
	}
	else
		*tokens = NULL;
	return (0);
}

t_redirects	*find_all_redir(t_list **tokens)
{
	t_redirects	*all_redir;

	all_redir = init_struct_redir();
	if (all_redir == NULL)
		return (NULL);
	if (find_redirect(tokens, all_redir) == -1)
	{
		freeing_memory_redirects(all_redir);
		return (NULL);
	}
	return (all_redir);
}

t_commands	*parser(t_data *data)
{
	t_commands	*commands;
	t_list		*tokens;

	commands = NULL;
	tokens = split_by_tokens(data);
	if (!(sintax_error(tokens)))
	{
		commands = init_struct_commands();
		if (commands == NULL)
		{
			ft_lstfree(&tokens);
			shell_exit(data, NULL, "malloc: *** error", 1);
		}
		parser_command_test(data, commands, tokens);
	}
	else
		ft_lstfree(&tokens);
	return (commands);
}

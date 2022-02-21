#include "minishell.h"

static void	create_token(t_data *data, t_list **tokens, char *content)
{
	*tokens = ft_lstnew(content);
	if (*tokens == NULL)
	{
		ft_free_tmp(content);
		ft_lstfree(tokens);
		shell_exit(data, NULL, "malloc: *** error", 1);
	}
}

void	is_token(t_data *data, size_t start, size_t end, t_list **tokens)
{
	char	*content;
	t_list	*token;

	content = ft_substr(data->input, start, end);
	if (content == NULL)
	{
		ft_lstfree(tokens);
		shell_exit(data, NULL, "malloc: *** error", 1);
	}
	if (tokens == NULL)
		create_token(data, tokens, content);
	else
	{
		token = ft_lstnew(content);
		if (token == NULL)
		{
			ft_free_tmp(content);
			ft_lstfree(tokens);
			shell_exit(data, NULL, "malloc: *** error", 1);
		}
		ft_lstadd_back(tokens, token);
	}
}

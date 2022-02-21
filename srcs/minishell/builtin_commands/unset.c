#include "../minishell.h"

static void	clearfree(t_listexp *new_list)
{
	free(new_list->name);
	if (new_list->value)
		free(new_list->value);
}

static void	del(void *new_list)
{
	clearfree((t_listexp *)new_list);
	free(new_list);
}

static int	deleteexp(t_commands *commands, t_data *data, int i)
{
	int		res;
	t_list	*node;
	t_list	*tmp;

	node = NULL;
	tmp = data->list_envp;
	while (tmp)
	{
		res = ft_strcmp(commands->cmd_arr[i], lnew_name(tmp));
		if (!res)
		{
			if (node)
				node->next = tmp->next;
			else
				data->list_envp = tmp->next;
			ft_lstdelone(tmp, del);
			return (1);
		}
		node = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_commands *commands, t_data *data)
{
	int		i;
	char	**temp;

	i = 1;
	while (i <= data->env_var)
	{
		if (commands->cmd_arr[i] == NULL)
		{
			temp = is_listarr(data->list_envp);
			ft_free_arr(data->envp);
			data->envp = temp;
			parse_env_in_data(data);
			return (-1);
		}
		if (commands->cmd_arr[i] && !check_name(commands->cmd_arr[i]))
		{
			printf("minishell: unset: %s: not a valid identifier\n", \
			commands->cmd_arr[i]);
			g_gl.status_exit = 1;
		}
		else
			deleteexp(commands, data, i);
		i++;
	}
	return (0);
}

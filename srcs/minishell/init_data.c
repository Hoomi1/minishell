#include "minishell.h"

void	parse_env_in_data(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			data->current_pwd = i;
		else if (!ft_strncmp(data->envp[i], "HOME=", 5))
			data->home_dir = i;
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
			data->old_pwd = i;
		else if (!ft_strncmp(data->envp[i], "PATH=", 5))
			data->path = i;
		if (ft_strncmp((data)->envp[i], "_=", 2) == 0)
			data->env_var = i;
	}
	data->count_str = i;
}

static void	duplicate_env(t_data *data, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (envp[i])
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (data->envp == NULL)
		shell_exit(data, NULL, "malloc: *** error", 1);
	while (++j != i)
	{
		data->envp[j] = ft_strdup(envp[j]);
		if (data->envp[j] == NULL)
			shell_exit(data, NULL, "malloc: *** error", 1);
	}
	data->envp[j] = NULL;
}

static t_list	*create_listexp(t_data *data)
{
	int			i;
	t_listexp	*export;
	t_list		*list;

	i = 0;
	list = NULL;
	while (i <= data->env_var)
	{
		export = add_str(i, data);
		ft_lstadd_back(&list, ft_lstnew(export));
		i++;
	}
	return (list);
}

static t_data	*create_data(int argc, char **argv)
{
	t_data	*new_struct;

	new_struct = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (new_struct == NULL)
		shell_exit(NULL, NULL, "malloc: *** error", 1);
	(void)argc;
	(void)argv;
	new_struct->home_dir = -1;
	new_struct->current_pwd = -1;
	new_struct->old_pwd = -1;
	new_struct->env_var = -1;
	new_struct->path = -1;
	new_struct->count_str = 0;
	new_struct->input = NULL;
	new_struct->fd0 = dup(0);
	new_struct->fd1 = dup(1);
	return (new_struct);
}

t_data	*init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = create_data(argc, argv);
	duplicate_env(data, envp);
	parse_env_in_data(data);
	data->list_envp = create_listexp(data);
	return (data);
}

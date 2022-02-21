#include "../minishell.h"

void	rer(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		printf("declare -x %s\n", temp[i]);
		i++;
	}
}

static void	print_export(char **temp)
{
	char	*str;
	int		i;
	int		sum;
	int		flag;

	flag = 1;
	while (flag == 1)
	{
		i = 0;
		flag = 0;
		while (temp[i] && temp[i + 1])
		{
			sum = ft_strcmp(temp[i], temp[i + 1]);
			if (sum > 0)
			{
				flag = 1;
				str = temp[i];
				temp[i] = temp[i + 1];
				temp[i + 1] = str;
			}
			i++;
		}
	}
	rer(temp);
}

static void	argum_export(t_commands *commands, t_list **list)
{
	t_listexp	export_new;
	int			i;

	i = 1;
	while (commands->cmd_arr[i] != NULL)
	{
		export_new.name = getname(commands->cmd_arr[i]);
		if (check_name(export_new.name))
		{
			export_new.value = getvalue(commands->cmd_arr[i]);
			if (!cheak_value(export_new.name, export_new.value, list))
				argum(export_new.name, export_new.value, list);
			if (export_new.value)
				free(export_new.value);
			free(export_new.name);
		}
		else
		{
			write_obser(export_new.name, commands, i);
			g_gl.status_exit = 1;
		}
		i++;
	}
	ft_lstadd_back(list, NULL);
}

void	ft_export(t_commands *commands, t_data *data)
{
	char	**temp;
	int		i;

	i = 0;
	if (commands->cmd_arr[1] == NULL)
	{
		temp = is_listarr(data->list_envp);
		print_export(temp);
		ft_free_arr(temp);
	}
	argum_export(commands, &data->list_envp);
	temp = is_listarr(data->list_envp);
	ft_free_arr(data->envp);
	data->envp = temp;
	parse_env_in_data(data);
}

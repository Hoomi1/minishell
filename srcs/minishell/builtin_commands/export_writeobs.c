#include "../minishell.h"

void	write_obser(char *name, t_commands *commands, int i)
{
	int	j;

	j = 0;
	if (ft_strcmp(name, "") != 0)
		printf("minishell: export: `%s': not a valid identifier\n" \
			, name);
	else if (commands->cmd_arr[i][j] == '=' && \
	commands->cmd_arr[i][j + 1] != '\0')
	{
		printf("minishell: export: `%s': not a valid identifier\n" \
				, commands->cmd_arr[i]);
	}	
	else if (!(ft_strcmp(commands->cmd_arr[i], "=")))
	{
		printf("minishell: export: `%s': not a valid identifier\n" \
			, commands->cmd_arr[i]);
	}
	free(name);
}

int	renamenode(t_list	*new_list, char *name, char *value)
{
	free(((t_listexp *)new_list->content)->name);
	if (((t_listexp *)new_list->content)->value)
		free(((t_listexp *)new_list->content)->value);
	((t_listexp *)new_list->content)->name = ft_strdup(name);
	if (value)
	{
		((t_listexp *)new_list->content)->value = ft_strdup(value);
		if (((t_listexp *)new_list->content)->value)
			return (-1);
	}
	else
		((t_listexp *)new_list->content)->value = NULL;
	if (!((t_listexp *)new_list->content)->name)
		return (-1);
	return (1);
}

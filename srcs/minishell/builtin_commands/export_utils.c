#include "../minishell.h"

char	*lnew_name(t_list *list)
{
	return (((t_listexp *)list->content)->name);
}

char	*lnew_value(t_list *list)
{
	return (((t_listexp *)list->content)->value);
}

t_listexp	*add_str(int i, t_data *data)
{
	t_listexp	*export;
	char		*str;

	export = (t_listexp *) malloc(sizeof(t_listexp));
	if (export == NULL)
		exit(1);
	str = ft_strchr(data->envp[i], '=');
	export->value = ft_strdup(++str);
	export->name = ft_strndup(data->envp[i], (str - data->envp[i]) - 1);
	return (export);
}

char	*equals_arr(char *name, char *value)
{
	char	*str;
	int		i;

	i = ft_strlen(name);
	i = i + ft_strlen(value);
	str = ft_calloc((i + 2), 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*name)
	{
		str[i] = *name;
		name++;
		i++;
	}
	str[i++] = '=';
	while (*value)
	{
		str[i] = *value;
		value++;
		i++;
	}
	return (str);
}

char	**is_listarr(t_list *list)
{
	char	*value;
	int		i;
	char	**new_arr;
	char	*name;

	i = ft_lstsize(list);
	new_arr = (char **) ft_calloc((i + 1), sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		value = lnew_value(list);
		name = lnew_name(list);
		if (value)
			new_arr[i] = equals_arr(name, value);
		else
			new_arr[i] = ft_strdup(name);
		if (!new_arr[i])
			return (NULL);
		list = list->next;
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

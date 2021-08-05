/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilstwo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:11:42 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/27 16:08:01 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getname(char *arr)
{
	char	*new;
	char	*name_new;
	int		i;

	i = 0;
	new = arr;
	while (arr[i] != '=' && arr[i] != '\0')
		i++;
	if (arr[i] == '\0')
	{
		name_new = ft_strdup(new);
		if (!name_new)
			return (NULL);
		return (name_new);
	}
	arr[i] = '\0';
	name_new = ft_strdup(new);
	if (!name_new)
		return (NULL);
	arr[i] = '=';
	return (name_new);
}

int	check_name(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str)
	{
		res = ft_isalpha(str[i]) || str[i] == '_';
		while (res && str[i] != '\0')
		{
			res = ft_isalnum(str[i]) || str[i] == '_';
			i++;
		}
	}
	return (res);
}

char	*getvalue(char *arr)
{
	char	*value_new;
	int		i;

	i = 0;
	while (arr[i] != '\0' && arr[i] != '=')
		i++;
	if (arr[i] == '\0')
		return (NULL);
	arr[i] = '\0';
	value_new = ft_strdup(&arr[i] + 1);
	if (!value_new)
		return (NULL);
	arr[i] = '=';
	return (value_new);
}

int	cheak_value(char *name, char *value, t_list **list)
{
	int		sum;
	t_list	*new_list;

	new_list = *list;
	while (new_list)
	{
		sum = ft_strcmp(name, ((t_listexp *)new_list->content)->name);
		if (!sum)
		{
			if (renamenode(new_list, name, value) == 1)
				return (1);
			else
				return (-1);
		}
		new_list = new_list->next;
	}
	return (0);
}

int	argum(char *name, char *value, t_list **list)
{
	t_listexp	*export;
	t_list		*new_list;

	export = (t_listexp *) malloc(sizeof(t_listexp));
	if (!export)
		return (-1);
	export->name = ft_strdup(name);
	if (value)
		export->value = ft_strdup(value);
	else
		export->value = NULL;
	new_list = ft_lstnew(export);
	if (!new_list)
		return (-1);
	ft_lstadd_back(list, new_list);
	return (0);
}

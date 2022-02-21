#include "minishell.h"

static void	shell_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": unclosed quotes", 2);
}

static void	check_open_close(char *str, size_t i, int *one, int *two)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && *one == 0)
		{
			*one = 1;
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\'')
				*one = 0;
		}
		else if (str[i] == '\"' && *two == 0)
		{
			*two = 1;
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
			if (str[i] == '\"')
				*two = 0;
		}
		if (str[i] != '\0')
			i++;
	}
}

static int	valid_input(t_data *data)
{
	int		quotes_one;
	int		quotes_two;

	quotes_one = 0;
	quotes_two = 0;
	if (ft_strlen(data->input) == 0)
		return (0);
	check_open_close(data->input, 0, &quotes_one, &quotes_two);
	if (quotes_one == 0 && quotes_two == 0)
		return (1);
	else
	{
		shell_error(data->input);
		return (0);
	}
	return (1);
}

void	executor(t_data *data, char *str)
{
	char		*tmp;
	t_commands	*commands;

	data->input = ft_strdup(str);
	if (data->input == NULL)
	{
		ft_free_tmp(str);
		shell_exit(data, NULL, "malloc: *** error", 1);
	}
	ft_free_tmp(str);
	tmp = ft_strtrim(data->input, " ");
	if (tmp == NULL)
		shell_exit(data, NULL, "malloc: *** error", 1);
	ft_bzero(data->input, ft_strlen(data->input));
	data->input = (char *)ft_memcpy(data->input, tmp, ft_strlen(tmp));
	ft_free_tmp(tmp);
	if ((valid_input(data)))
	{
		commands = parser(data);
		execute_commands(data, commands);
		freeing_memory_commands(commands);
	}
	ft_free_tmp(data->input);
}

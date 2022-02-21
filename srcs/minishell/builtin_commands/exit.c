#include "../minishell.h"

static int	cheack_dig(t_commands *com)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(com->cmd_arr[1][i]) != 0)
		i++;
	if (i == ft_strlen(com->cmd_arr[1]))
		return (1);
	return (0);
}

static int	equalsmy(char *str, int sign)
{
	int		i;
	char	*equals1;

	if (sign == -1)
		equals1 = "9223372036854775808";
	else
		equals1 = "9223372036854775807";
	i = 0;
	while (str[i])
	{
		if (str[i] > *equals1)
			return (0);
		i++;
		equals1++;
	}
	return (1);
}

static int	check_num(int sign, char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) || i > 18)
			return (0);
		i++;
	}
	if (i == 19)
	{
		return (equalsmy(str, sign));
	}
	return (1);
}

static size_t	my_smotrdig(char *str, int *i)
{
	int		sign;
	size_t	res;

	sign = 1;
	res = 0;
	*i = 1;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	if (*str == '+')
		str++;
	if (!check_num(sign, str))
	{
		*i = 0;
		return (0);
	}
	while (*str)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

void	ft_exit(t_commands *commands, t_data *data)
{
	int	i;
	int	fl_exit;

	fl_exit = 0;
	write(0, "exit\n", 5);
	if (commands->cmd_arr[1] == NULL)
		succes_exit(data, commands, fl_exit);
	if (cheack_dig(commands) == 1)
	{
		g_gl.status_exit = my_smotrdig(commands->cmd_arr[1], &i);
		prover_exit(commands, &fl_exit, i);
		succes_exit(data, commands, fl_exit);
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", \
		commands->cmd_arr[1]);
		g_gl.status_exit = 255;
		fl_exit = 0;
		succes_exit(data, commands, fl_exit);
	}
}

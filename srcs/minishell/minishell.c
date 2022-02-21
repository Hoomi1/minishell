#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = init_data(argc, argv, envp);
	term(data);
	return (0);
}

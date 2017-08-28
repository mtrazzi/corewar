#include "vm.h"

# define STR_ERR_USAGE	"usage: corewar [-dump nbr_cycles] \
[[-n number] champion1.cor] ..."

# define STR_ERR_FILE "could not read .cor file"

int		ft_is_valid_ext(char *file_name, char *extension)
{
	while (*file_name != '.')
		file_name++;
	return (!ft_strcmp(file_name, extension));
}

int		ft_check_option(t_env *e, int i, int ac, char **av)
{
	if (!(!ft_strcmp(av[i] + 1, "dump") || !ft_strcmp(av[i] + 1, "n")) || \
		i + 1 >= ac)
		return (-1);
	return (1);
}

int		parse_arg_vm(int ac, char **av, t_env *e)
{
	int i;
	int ret;

	if (ac < 2)
		return (ft_error_vm(e, STR_ERR_USAGE));
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if ((ret = ft_check_option(e, i, ac, av)) < 0) 
				return (ft_error_vm(e, STR_ERR_USAGE));
			i += ret;
		}
		else if (!ft_is_valid_ext(av[i], ".cor") || ft_parse_file(e, av[i]) < 0)
			return (ft_error_vm(e, STR_ERR_FILE));
		i++;
	}
	return (0);
}

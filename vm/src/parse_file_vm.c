#include "vm.h"

# define STR_ERR_READ_FILE "could not read .cor file"
# define STR_ERR_CLOSE_FILE "could not close .cor file"
# define STR_ERR_FORMAT_FILE ".cor file not well formated"
# define STR_ERR_MAGIC "magic number incorrect"

int		parse_header(t_env *e, int i, int fd)
{
	char 	buff[4];
	int		padding;

	if (read(fd, (char *)&e->par.champions[i].magic, 4) < 4)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	e->par.champions[i].magic = convert_uint(e->par.champions[i].magic);
	if (e->par.champions[i].magic != COREWAR_EXEC_MAGIC)
		return (ft_error_vm(ERR_MAGIC, STR_ERR_MAGIC));
	if (read(fd, e->par.champions[i].name, PROG_NAME_LENGTH + 1) < PROG_NAME_LENGTH)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	padding = (4 - (PROG_NAME_LENGTH + 1) % 4) % 4;
	if (read(fd, buff, padding) < padding)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	if (read(fd, (char *)&e->par.champions[i].prog_size, 4) < 4)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	e->par.champions[i].prog_size = convert_uint(e->par.champions[i].prog_size);
	if (read(fd, e->par.champions[i].comment, COMMENT_LENGTH + 1) < COMMENT_LENGTH)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	padding = (4 - (COMMENT_LENGTH + 1) % 4) % 4;
	if (read(fd, buff, padding) < padding)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	return (0);
}

int		parse_file(t_env *e, int i)
{
	int fd;

	if ((fd = open(e->par.champions[i].file_name, O_RDONLY)) < 0)
		return (ft_perror_vm(ERR_OPEN_FILE));
	if (parse_header(e, i, fd) < 0)
		return (ft_error_vm(ERR_FORMAT_FILE, STR_ERR_FORMAT_FILE));
	if (close(fd) < 0)
		return (ft_perror_vm(ERR_CLOSE_FILE));
	return (0);
}

int		parse_all_files(t_env *e)
{
	int i;
	int ret;

	i = 0;
	while (i < e->par.nb_chp)
	{
		if ((ret = parse_file(e, i)) < 0)
			return (ft_error_vm(ret, STR_ERR_READ_FILE));
		i++;
	}
	return (1);
}

#include "asm.h"

static int	ft_is_valid_ext(char *file_name, char *extension)
{
	while (*file_name != '.')
		file_name++;
	return (!ft_strcmp(file_name, extension));
}

int			ft_file_to_lst_asm(t_asm *e, char *file_name)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	if (!ft_is_valid_ext(file_name, ".s"))
		return (ft_error_asm(e, "not a valid extension. \".s\" extension expected"));
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (ft_perror_asm(e));
	while ((ret = get_next_line(fd, &line)) > 0)
		dll_append(&e->lst, dll_new(line));
	if (close(fd) < 0 || ret < 0)
		return (ft_perror_asm(e));
	return (0);
}

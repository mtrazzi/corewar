#include "asm.h"

int			update_fd_asm(t_asm *a, char *file_name)
{
	int		size_name;
	char	*new_filename;

	size_name = ft_strlen(file_name) - 2;
	new_filename = ft_strnew(size_name + 4);
	if (!new_filename)
		return (-1);//MAL_ERR
	ft_strncpy(new_filename, file_name, size_name);
	ft_strcpy(new_filename + size_name, ".corr");//CHANGE
	a->fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (a->fd < 0)
		return (-1);
	return (1);
}

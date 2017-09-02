#include "asm.h"

static int	new_cor_file(char *file_name)
{
	char	*new_name;

	*ft_strchr(file_name, '.') = '\0';
	new_name = ft_strjoin(file_name, ".cor");//NON!
	return (open(new_name, O_WRONLY | O_CREAT | O_TRUNC , 0644));
}

int			update_fd_asm(t_asm *e, char *file_name)
{
	e->fd = new_cor_file(file_name);//errors
	return (e->fd);
}

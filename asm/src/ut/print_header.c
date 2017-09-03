#include "asm.h"

void	print_padding(int fd, int octets)
{
	while (octets--)
		ft_fprintf(fd, "%hhu", 0);
}


void	write_header(t_asm *a)
{
	int	i;

	ft_fprintf(a->fd, "%u", a->header.magic);
	i = -1;
	while (++i < PROG_NAME_LENGTH)
		ft_fprintf(a->fd, "%c", a->header.prog_name[i]);
	print_padding(a->fd, 8 - (sizeof(a->header.magic) + PROG_NAME_LENGTH) % 8);
	ft_fprintf(a->fd, "%u", a->header.prog_size);
	ft_fprintf(a->fd, "%s", a->header.comment);
	//ft_write_be(fd, t.magic);
	//write(fd, t.prog_name, PROG_NAME_LENGTH);
	//ft_write_be(fd, t.prog_size);
	//write(fd, t.comment, COMMENT_LENGTH);
}

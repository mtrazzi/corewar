#include "asm.h"

void	ft_write_header(int fd, header_t t)
{
	ft_write_be(fd, t.magic);
	write(fd, t.prog_name, PROG_NAME_LENGTH);
	ft_write_be(fd, t.prog_size);
	write(fd, t.comment, COMMENT_LENGTH);
}

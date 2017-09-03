#include "asm.h"

void	print_header(t_asm *a)
{
	char	tab[16];
	int		paddings[2];
	int		mod;

	mod = (sizeof(a->header.magic) + PROG_NAME_LENGTH) % 8;
	paddings[0] = 8 - (mod == 0 ? 8 : mod);
	mod = (sizeof(a->header.magic) + PROG_NAME_LENGTH
			+ sizeof(a->header.prog_size) + COMMENT_LENGTH + paddings[0]) % 16;
	paddings[1] = 16 - (mod == 0 ? 16 : mod);
	//ft_bzero(tab, 16);
	int i = -1;
	while (++i < 16)
		tab[i] = 0xff;//change that!
	write_be(a->fd, a->header.magic, sizeof(a->header.magic));
	write(a->fd, a->header.prog_name, PROG_NAME_LENGTH);
	write(a->fd, tab, paddings[0]);
	write_be(a->fd, a->header.prog_size, sizeof(a->header.prog_size));
	write(a->fd, a->header.comment, COMMENT_LENGTH);
	write(a->fd, tab, paddings[1]);
}

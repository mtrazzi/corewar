#include "asm.h"

u_int	ft_convert_endian(u_int n)
{
	u_int b0;
	u_int b1;
	u_int b2;
	u_int b3;

	b0 = (0x000000ff & n) << 24;
	b1 = (0x0000ff00 & n) << 8;
	b2 = (0x00ff0000 & n) >> 8;
	b3 = (0xff000000 & n) >> 24;
	return (b0 | b1 | b2 | b3);
}

void	ft_print_hexa(u_int n)
{
	uint32_t b0;
	uint32_t b1;
	uint32_t b2;
	uint32_t b3;

	b0 = (0x000000ff & n);
	b1 = (0x0000ff00 & n) >> 8;
	b2 = (0x00ff0000 & n) >> 16;
	b3 = (0xff000000 & n) >> 24;
	ft_printf("|%x %x %x %x|\n", b3, b2, b1, b0);
}

/*
** Write in big endian
*/

void	ft_write_be(int fd, u_int n, u_int size)
{
	u_int	k;
	char	*s;

	k = ft_convert_endian(n);
	s = (char *)&k;
	write(fd, s + (4 - size), size); 
}

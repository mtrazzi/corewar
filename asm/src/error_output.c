#include "asm.h"

int		error_parse(t_parse *p)
{
	ft_printf("Error at [line, char][%d, %d]: {%s}\n",
				p->line_count + 1, p->alc - p->add_line_start + 1, p->alc);
	return (1);
}
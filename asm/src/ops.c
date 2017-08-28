#include "asm.h"

int		ft_strncmp_modified(char *s1, char *s2, size_t n)
{
	while ((*s1 && *s2) && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	if (n == 1 && *s1 == '\0')//n= 0?
		return (0);
	return (1);
}

t_op	*does_op_exist_in_op_tab()
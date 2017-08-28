#include "asm.h"

#define NAME_DIFFERENT 0
#define NAME_EQUAL 1

int		compare_op_names(char *str, int len, char *op_name)
{
	if (ft_strlen(op_name) != len)
		return (NAME_DIFFERENT);
	if (ft_strncmp(op_name, str, len) == 0)
		return (NAME_EQUAL);
	return (NAME_DIFFERENT);
}

t_op	*does_op_exist_in_op_tab(char *str, int len)
{
	int		i;

	i = -1;
	while (++i < MAX_OP)
	{
		if (compare_op_names(str, len, g_op_tab[i].name) == NAME_EQUAL)
			return (&g_op_tab[i]);
	}
	return (NULL);
}

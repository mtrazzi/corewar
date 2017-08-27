#include "asm.h"

t_arg_type	ft_give_type(char *param)
{
	if (*param == 'r')
		return (T_REG);
	else if (*param == '%')
		return (T_DIR);
	else
		return (T_IND);
}

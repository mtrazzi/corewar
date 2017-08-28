#include "asm.h"

t_sym	*create_sym(char *label, u_int symbol)
{
	t_sym	*new;

	new = (t_sym *)malloc(sizeof(t_sym));
	if (new == NULL)
		return (NULL);
	new->label = label;
	new->sym = symbol;
	return (new);
}
#include "asm.h"
 
int main(void)
{
	t_asm *e;
	e = ft_init_asm();

	ft_add_to_end("first line", &e->lst_op);
	ft_add_to_end("second line", &e->lst_op);
	ft_add_to_end("third line", &e->lst_op);
	ft_print_lst_op(e->lst_op);
	ft_free_asm_env(e);

	return (0);
}

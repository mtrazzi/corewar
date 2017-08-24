#include "asm.h"

void	ft_free_content(void *content)
{
	ft_memdel(&content);	
}

void	ft_free_asm_env(t_asm *e)
{
	dll_del(&e->lst);
	ft_memdel((void **)&e);
}

#include "vm.h"

int     do_process(t_env *e, t_prc *prc)
{
    u_char  op_code;

    op_code = e->map[prc->pc];
    if (!op_code || op_code > 16)
    {
        prc->pc = (prc->pc + 1) % MEM_SIZE;
        return (0);
    }
    //prc->pc = (prc->pc + 1) % MEM_SIZE;         //just to see if cursor moves
    if (prc->cyc_left == 0)
        prc->cyc_left = g_op_tab[op_code - 1].nb_cycles;
    prc->cyc_left -= 1;
    if (prc->cyc_left == 0)
        g_op_fun_tab[op_code - 1](e, prc);    
    return (0);
}

#include "vm.h"

# define OP_ZJMP 0x09

int     do_process(t_env *e, t_prc *prc)
{
    u_char  op_code;

    op_code = e->map[prc->pc];
    if (!op_code || op_code > 16)                       //op_code not valid
    {
        prc->pc = (prc->pc + 1) % MEM_SIZE;
        return (0);
    }
    if (prc->cyc_left == 0)                             //cursor just moved on byte
        prc->cyc_left = g_op_tab[op_code - 1].nb_cycles;
    prc->cyc_left -= 1;
    if (prc->cyc_left == 0)                             //all cycles have passed
    {
        g_op_fun_tab[op_code - 1](e, prc);
        if (op_code != OP_ZJMP || !(prc->carry))        //do not do this if zjmp and carry == 1
            prc->pc = (prc->pc + nb_bytes_to_skip(op_code, \
            e->map[(prc->pc + 1) % MEM_SIZE])) % MEM_SIZE;
    }
    return (0);
}

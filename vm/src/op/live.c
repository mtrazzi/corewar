#include "vm.h"

int     live(t_env *e, t_prc *prc)
{
    u_int nb;

    nb = convert_4_bytes(e->map[(prc->pc + 0) % MEM_SIZE], \
                         e->map[(prc->pc + 1) % MEM_SIZE], \
                         e->map[(prc->pc + 2) % MEM_SIZE], \
                         e->map[(prc->pc + 3) % MEM_SIZE]);
    prc->live += 1;
    prc->live_nb = nb;
    return (0);
}

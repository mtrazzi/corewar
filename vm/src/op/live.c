#include "vm.h"

int     live(t_env *e, t_prc *prc)
{
    prc->live += 1;
    prc->live_nb = get_value(e, DIR_CODE, prc, prc->pc + 1);
    if (is_real_number(e, prc->live_nb))
        e->last_alive = prc->live_nb;
    if (e->par.verb)
        ft_printf("P    %d | live %d\n", prc->id, prc->live_nb);
    return (0);
}

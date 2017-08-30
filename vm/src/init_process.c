#include "vm.h"

# define STR_ERR_MALLOC_PRC "could not malloc process"

static void    init_reg(t_prc *prc)
{
    int i;

    i = 0;
    while (i < REG_NUMBER)
        prc->r[i++] = 0;
}

t_prc   *new_prc(u_int pc, int nb, int id)
{
    t_prc *prc;

    if (!(prc = (t_prc *)malloc(sizeof(t_prc))))
        return (NULL);
    init_reg(prc);
    prc->r[0] = nb;
    prc->pc = pc;
    prc->carry = 0;
    prc->live = 0;
    prc->id = id;
    return (prc);
}

int     init_all_processes(t_env *e)
{
    u_int i;
    t_prc *prc;

    i = 0;
    while (i < e->par.nb_chp)
    {
        if (!(prc = new_prc((MEM_SIZE / e->par.nb_chp) * i, \
                            e->par.champions[i].nb, i)))
            return (ft_error_vm(STR_ERR_MALLOC_PRC));
        dll_push_front(&e->prc_lst, dll_new(prc));
        e->map_color[(MEM_SIZE / e->par.nb_chp) * i] += 1;
        i++;
    }
    return (0);
}

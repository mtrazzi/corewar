#include "vm.h"

# define PAR_SIZE_REG 1
# define PAR_SIZE_IND 2
# define DEBUG_GET_INDEX 0
# define DEBUG_GET_VALUE 1

u_int   mod(int nbr, u_int mod)
{
    while (nbr < 0)
        nbr += mod;
    return (nbr % mod);
}


int     sizeof_param(u_char op_code, u_char type_of_param)
{
    if (type_of_param == REG_CODE)
        return (PAR_SIZE_REG);
    else if (type_of_param == IND_CODE)
        return (PAR_SIZE_IND);
    else if (type_of_param == DIR_CODE)
        return (4 - 2 * (g_op_tab[op_code - 1].last_arg));
    return (0);
}

int     nb_bytes_to_skip(u_char op_code, u_char ocp)
{
    int sum;

    if (!(g_op_tab[op_code - 1].ocp))           //for live, zjmp, etc.
        return (1 + (op_code == 1 ? 4 : 2));
    sum = 2;                                    //op_code + ocp
    while (ocp > 0)
    {
        sum += sizeof_param(op_code, ocp % 4);  //two last bits
        ocp /= 4;
    }
    return (sum);
}

int     get_value(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
    int index;
    int addr;

    if (type_of_param == REG_CODE)
        return (prc->r[e->map[pos]]);
    else if (type_of_param == DIR_CODE)
        return ((int)convert_4_bytes(e->map[(pos + 0) % MEM_SIZE], \
                                e->map[(pos + 1) % MEM_SIZE], \
                                e->map[(pos + 2) % MEM_SIZE], \
                                e->map[(pos + 3) % MEM_SIZE]));
    index = convert_2_bytes(e->map[pos], e->map[(pos + 1) % MEM_SIZE]);
    addr = prc->pc + (index % IDX_MOD);
    return (convert_4_bytes(e->map[(addr + 0) % MEM_SIZE],
							e->map[(addr + 1) % MEM_SIZE],
							e->map[(addr + 2) % MEM_SIZE],
							e->map[(addr + 3) % MEM_SIZE]));
}

int     is_real_number(t_env *e, int nb)
{
    u_int i;

    i = 0;
    while (i < e->par.nb_chp)
    {
        if (e->par.champions[i].nb == nb)
            return (i + 1);
        i++;
    }
    return (0);
}

short	get_index(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
    if (type_of_param == REG_CODE)
        return (prc->r[e->map[pos]]);
    if (DEBUG_GET_INDEX)
        ft_printf("get_index : %2x %2x\n", e->map[pos], e->map[pos + 1]);
    else if (type_of_param == DIR_CODE)
        return ((short)convert_2_bytes(e->map[(pos + 0) % MEM_SIZE], \
                                e->map[(pos + 1) % MEM_SIZE]));
    return ((short)convert_2_bytes(e->map[pos], e->map[(pos + 1) % MEM_SIZE]));
}

void copy_value(int value, t_env *e, u_int pos)
{
    e->map[(pos + 0 % MEM_SIZE)] = value >> 24;
    e->map[(pos + 1 % MEM_SIZE)] = ((value << 8) >> 24);
    e->map[(pos + 2 % MEM_SIZE)] = ((value << 16) >> 24);
    e->map[(pos + 3 % MEM_SIZE)] = ((value << 24) >> 24);
}

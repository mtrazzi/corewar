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

u_int	mod_map(int nbr)
{
    while (nbr < 0)
        nbr += MEM_SIZE;
	return (nbr % MEM_SIZE);
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
	u_int i;

    if (!(g_op_tab[op_code - 1].ocp))           //for live, zjmp, etc.
        return (1 + (op_code == 1 ? 4 : 2));
    sum = 2;                                    //op_code + ocp
	i = 0;
    while (i < g_op_tab[op_code - 1].nb_param)
    {
        sum += sizeof_param(op_code, (ocp >> (6 - 2 * i)) & LAST_TWO_BITS);  //two last bits
		i++;
    }
    return (sum);
}

int     get_value(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
    int index;
    int addr;

    if (type_of_param == REG_CODE)
        return (prc->r[e->map[mod_map(pos)]]);
    else if (type_of_param == DIR_CODE)
        return (convert_4_bytes(e->map[mod_map(pos + 0)],
                                e->map[mod_map(pos + 1)],
                                e->map[mod_map(pos + 2)],
                                e->map[mod_map(pos + 3)]));
    index = convert_2_bytes(e->map[pos], e->map[(pos + 1)]);
    addr = prc->pc + (index % IDX_MOD);
    return (convert_4_bytes(e->map[mod_map(addr + 0)],
							e->map[mod_map(addr + 1)],
							e->map[mod_map(addr + 2)],
							e->map[mod_map(addr + 3)]));
}

int     lget_value(t_env *e, u_char type_of_param, t_prc *prc, u_int pos)
{
    int index;
    int addr;

    if (type_of_param == REG_CODE)
        return (prc->r[e->map[mod_map(pos)]]);
    else if (type_of_param == DIR_CODE)
        return (convert_4_bytes(e->map[mod_map(pos + 0)],
                                e->map[mod_map(pos + 1)],
                                e->map[mod_map(pos + 2)],
                                e->map[mod_map(pos + 3)]));
    index = convert_2_bytes(e->map[pos], e->map[(pos + 1)]);
    addr = prc->pc + index;
    return (convert_4_bytes(e->map[mod_map(addr + 0)],
							e->map[mod_map(addr + 1)],
							e->map[mod_map(addr + 2)],
							e->map[mod_map(addr + 3)]));
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
        return (prc->r[e->map[mod_map(pos)]]);
    return (convert_2_bytes(e->map[mod_map(pos)], e->map[mod_map(pos + 1)]));
}

void copy_value(int value, t_env *e, u_int pos)
{
    e->map[mod_map(pos + 0)] = value >> 24;
    e->map[mod_map(pos + 1)] = ((value << 8) >> 24);
    e->map[mod_map(pos + 2)] = ((value << 16) >> 24);
    e->map[mod_map(pos + 3)] = ((value << 24) >> 24);
}

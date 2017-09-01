#include "vm.h"

int     nb_bytes_to_skip(u_char op_code, u_char ocp)
{
    if (!(g_op_tab[op_code - 1].ocp))
        return (1 + (op_code == 1 ? 4 : 2));
}

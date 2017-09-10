#include "vm.h"

# define B0 0x000000ff
# define B1 0x0000ff00
# define B2 0x00ff0000
# define B3 0xff000000

int   ft_is_number(char *str)
{
  if (*str == '-' && *(str + 1) < '9' && *(str + 1) > '0')
    str++;
  while (*str)
  {
    if (*str > '9' || *str < '0')
      return (0);
    str++;
  }
  return (1);
}

int   ft_is_int(char *str)
{
  if (!ft_is_number(str))
    return (0);
  if (ft_strlen(str) > 11)
    return (0);
  if (ft_atol(str) < INT_MIN || ft_atol(str) > INT_MAX)
   return (0);
  return (1);
}

u_int   convert_uint(u_int n)
{
    return ((n & B0) << 24 | (n & B1) << 8 | (n & B2) >> 8
    | (n & B3) >> 24);
}

u_int   convert_ushort(u_short n)
{
    return ((n & B0) << 8 | (n & B1) >> 8);
}

void    color_tab(void)
{
 g_color_tab[0] = "";
 g_color_tab[1] = "\033[0;32m";          //green
 g_color_tab[2] = "\033[0;30m\033[42m";  //black on green
 g_color_tab[3] = "\033[0;34m";          //blue
 g_color_tab[4] = "\033[0;30m\033[44m";  //black on blue
 g_color_tab[5] = "\033[0;31m";          //red
 g_color_tab[6] = "\033[0;30m\033[41m";  //black on red
 g_color_tab[7] = "\033[0;36m";          //cyan
 g_color_tab[8] = "\033[0;30m\033[46m";  //black on cyan
 g_color_tab[9] = NULL;
}

void    op_tab_init(void)
{
	g_op_tab[0] = (t_op){"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
	g_op_tab[1] = (t_op){"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0};
	g_op_tab[2] = (t_op){"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0};
	g_op_tab[3] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0};
	g_op_tab[4] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0};
	g_op_tab[5] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, \
							"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	g_op_tab[6] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, \
							"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	g_op_tab[7] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, \
							"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	g_op_tab[8] = (t_op){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1};
	g_op_tab[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, \
							"load index", 1, 1};
	g_op_tab[10] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, \
							"store index", 1, 1};
	g_op_tab[11] = (t_op){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1};
	g_op_tab[12] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0};
	g_op_tab[13] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, \
							"long load index", 1, 1};
	g_op_tab[14] = (t_op){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1};
	g_op_tab[15] = (t_op){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0};
	// g_op_tab[16] = (t_op){0, 0, {0}, 0, 0, 0, 0, 0}; //op_code 17, nb_cycle 1
	g_op_tab[16] = (t_op){0, 0, {0}, 17, 1, 0, 0, 0};
}

int		convert_4_bytes(u_char b0, u_char b1, u_char b2, u_char b3)
{
    return (((int)b0) << 24 | ((int)b1) << 16 | ((int)b2) << 8 | \
            ((int)b3));
}

short	convert_2_bytes(u_char b0, u_char b1)
{
    return ((short)(((int)b0) << 8 | ((int)b1)));
}

void    op_fun_tab_init(void)
{
    g_op_fun_tab[0] = &live;
    g_op_fun_tab[1] = &ld;
    g_op_fun_tab[2] = &st;
    g_op_fun_tab[3] = &add;
    g_op_fun_tab[4] = &sub;
    g_op_fun_tab[5] = &and;
    g_op_fun_tab[6] = &or;
    g_op_fun_tab[7] = &xor;
    g_op_fun_tab[8] = &zjmp;
    g_op_fun_tab[9] = &ldi;
    g_op_fun_tab[10] = &sti;
    g_op_fun_tab[11] = &ft_fork;
    g_op_fun_tab[12] = &lld;
    g_op_fun_tab[13] = &lldi;
    g_op_fun_tab[14] = &lfork;
    g_op_fun_tab[15] = &aff;
    g_op_fun_tab[16] = NULL;
}

void    clear_screen(void)
{
    printf("\033[2J");
}

int		dump(t_env *e)
{
	int i;
	int j;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("0x%04x : ", i);
		j = -1;
		while (++j < 64)
			printf("%02x ", e->map[i + j]);
		printf("\n");
		i += 64;
	}
	return (0);
}


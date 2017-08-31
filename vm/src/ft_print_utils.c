#include "vm.h"

# define BYTES_PER_LINE 64
# define END_OF_COLOR "\e[0m"

static void change_color_prc(t_env *e, int incr)
{
    t_dll *prc_lst;
    t_prc *prc;

    prc_lst = e->prc_lst;
    while (prc_lst)
    {
        prc = (t_prc *)(prc_lst->content);
        e->map_color[prc->pc] += incr;
        prc_lst = prc_lst->next;
    }
}

void print_map(t_env e)
{
  int nb_bytes;
  int j;
  char *color;

  nb_bytes = 0;
  change_color_prc(&e, 1);
  while (nb_bytes < MEM_SIZE)
  {
    j = 0;
    while (j < BYTES_PER_LINE)
    {
      color = g_color_tab[e.map_color[nb_bytes + j]];
      ft_printf("%s%02x%s ", color, e.map[nb_bytes + j], END_OF_COLOR);
      j++;
    }
	ft_printf("\n");
    nb_bytes += BYTES_PER_LINE;
  }
  change_color_prc(&e, -1);
}

void print_env(t_env e)
{
	u_int   i;
    t_chp chp;

    print_map(e);
	ft_printf("\nNb of cycles to die        : %d\n", e.cyc);
	ft_printf("Nb of lives since last check : %d\n", e.nb_live);
	ft_printf("Is there dump ?              : %s\n", (e.par.dump ? "yes" : "no"));
	ft_printf("The dump will be in          : %d cycles\n", e.par.nb_cyc);
	ft_printf("There are                    : %d champions\n\n", e.par.nb_chp);
	i = 0;
	while (i < e.par.nb_chp)
	{
    chp = e.par.champions[i];
    ft_printf("CHAMPION:\n");
    ft_printf("         nb :        %d\n", chp.nb);
    ft_printf("         file_name : %s\n", chp.file_name);
    ft_printf("         magic     : %x\n", chp.magic);
    ft_printf("         name      : |%s|\n", chp.name);
    ft_printf("         prog_size : %u\n", chp.prog_size);
    ft_printf("         comment   : |%s|\n", chp.comment);
    i++;
	}
}

int print_prc(t_prc *prc)
{
    int i;

    ft_printf("pc is : %u\n", prc->pc);
    i = 0;
    while (i < REG_NUMBER)
    {
        ft_printf("     r%d is : %d\n", i, prc->r[i]);
        i++;
    }
    ft_printf("carry is     : %d\n", prc->carry);
    ft_printf("live is      : %d\n", prc->live);
    ft_printf("live_nb is   : %d\n", prc->live_nb);
    ft_printf("id is        : %d\n", prc->id);
    ft_printf("cyc_left is  : %d\n", prc->cyc_left);
    return (0);
}

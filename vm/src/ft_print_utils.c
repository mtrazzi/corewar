#include "vm.h"

# define BYTES_PER_LINE 64
# define END_OF_COLOR "\e[0m"
# define PRINT_NB_CYC 1

static    void change_color_prc(t_env *e, int incr)
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

void    print_map(t_env e)
{
  int nb_bytes;
  int j;
  char *color;

  nb_bytes = 0;
  change_color_prc(&e, 1);
  if (PRINT_NB_CYC)
    printf("NB OF CYCLES SINCE BEGINNING : %d\nCYCLES PER STEP : %d\n",
	e.cyc_since_beg - 1, e.speed);
  while (nb_bytes < MEM_SIZE)
  {
    j = 0;
    while (j < BYTES_PER_LINE)
    {
      color = g_color_tab[e.map_color[nb_bytes + j]];
      printf("%s%02x%s ", color, e.map[nb_bytes + j], END_OF_COLOR);
      j++;
    }
	printf("\n");
    nb_bytes += BYTES_PER_LINE;
  }
  change_color_prc(&e, -1);
}

void    print_env(t_env e)
{
	u_int   i;
    t_chp chp;

    print_map(e);
	printf("\nNb of cycles to die        : %d\n", e.cyc);
	printf("Nb of lives since last check : %d\n", e.nb_live);
	printf("Is there dump ?              : %s\n", (e.par.dump ? "yes" : "no"));
	printf("The dump will be in          : %d cycles\n", e.par.nb_cyc);
	printf("There are                    : %d champions\n\n", e.par.nb_chp);
	i = 0;
	while (i < e.par.nb_chp)
	{
    chp = e.par.champions[i];
    printf("CHAMPION:\n");
    printf("         nb :        %d\n", chp.nb);
    printf("         file_name : %s\n", chp.file_name);
    printf("         magic     : %x\n", chp.magic);
    printf("         name      : |%s|\n", chp.name);
    printf("         prog_size : %u\n", chp.prog_size);
    printf("         comment   : |%s|\n", chp.comment);
    i++;
	}
}

int     print_prc(t_prc *prc)
{
    int i;

    printf("pc is : %u\n", prc->pc);
    i = 0;
    while (i < REG_NUMBER)
    {
        printf("     r%d is : %d\n", i, prc->r[i]);
        i++;
    }
    printf("carry is     : %d\n", prc->carry);
    printf("live is      : %d\n", prc->live);
    printf("live_nb is   : %d\n", prc->live_nb);
    printf("id is        : %d\n", prc->id);
    printf("cyc_left is  : %d\n", prc->cyc_left);
    return (0);
}

void    print_introduction(t_env *e)
{
    u_int i;
    t_chp chp;

    printf("%s\n", "Introducing contestants...");
    i = 0;
    while (i < e->par.nb_chp)
    {
        chp = e->par.champions[i];
        printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n", \
        i + 1 , chp.prog_size, chp.name, chp.comment);
        i++;
    }
}

void    print_conclusion(t_env *e)
{
    u_int i;
    t_chp chp;

    i = 0;
    while (i < e->par.nb_chp)
    {
        chp = e->par.champions[i];
        if (chp.nb == e->last_alive)
            printf("Contestant %d, \"%s\", has won !\n", i + 1, chp.name);
        i++;
    }
}

void	print_ADV(t_env *e, int pos, int skip)
{
	int i;

	printf("ADV %d (0x%04x -> 0x%04x) ", skip, pos, pos + skip);//04 depends on map size
	i = -1;
	while (++i < skip)
		printf("%02x ", e->map[mod_map(pos + i)]);
	printf("\n");
}

void    dump(t_env *e)
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
}

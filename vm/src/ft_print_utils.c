#include "vm.h"

# define BYTES_PER_LINE 64

void print_map(t_env e)
{
  int nb_bytes;
  int j;

  nb_bytes = 0;
  while (nb_bytes < MEM_SIZE)
  {
    j = 0;
    while (j < BYTES_PER_LINE)
    {
		if (e.map[nb_bytes + j] < 16)
			ft_printf("0");
		ft_printf("%x ", e.map[nb_bytes + j]);
		j++;
    }
	ft_printf("\n");
    nb_bytes += BYTES_PER_LINE;
  }
}

void print_env(t_env e)
{
	int i;
  t_chp chp;

  print_map(e);
	ft_printf("\nNb of cycles to die          : %d\n", e.cyc);
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
    ft_printf("         prog_size : %x\n", chp.prog_size);
    ft_printf("         comment   : |%s|\n", chp.comment);
    i++;
	}
}

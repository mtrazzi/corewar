/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philippe <Philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:05:12 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/07 16:21:07 by Philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define HA ("(Default is to hide it)")
#define HSEP ("###############################")
#define HV ("together to enable several")
#define HMC ("(controls available on screen)")

int		help(void)
{
	ft_printf("   -a		  : Prints output from \"aff\" %s\n", HA);
	ft_printf("   -n N		: define champion number\n");
	ft_printf("#### TEXT OUTPUT MODE ###########################%s\n", HSEP);
	ft_printf("   -dump N	: Dumps memory after N cycles then exits\n");
	ft_printf("   -v N		: Verbosity levels, can be added %s\n", HV);
	ft_printf(" 		- 0 : Show only essentials\n");
	ft_printf(" 		- 1 : Show lives\n");
	ft_printf(" 		- 2 : Show cycles\n");
	ft_printf(" 		- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf(" 		- 8 : Show deaths\n");
	ft_printf(" 		- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("#### NCURSES OUTPUT MODE %s########################\n", HSEP);
	ft_printf("   -m		: Ncurses output mode %s\n", HMC);
	ft_printf("%s#################################################\n", HSEP);
	return (1);
}

void	print_introduction(t_env *e)
{
	u_int i;
	t_chp chp;

	ft_printf("%s\n", "Introducing contestants...");
	i = 0;
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",\
				i + 1, chp.prog_size, chp.name, chp.comment);
		i++;
	}
}

void	print_conclusion(t_env *e)
{
	u_int i;
	t_chp chp;

	i = 0;
	while (i < e->par.nb_chp)
	{
		chp = e->par.champions[i];
		if (chp.nb == e->last_alive)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", i + 1, chp.name);
			return ;
		}
		i++;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", i, chp.name);
}

void	print_adv(t_env *e, int pos, int skip)
{
	int i;

	ft_printf("ADV %d (0x%04x -> 0x%04x) ", skip, pos, pos + skip);
	i = -1;
	while (++i < skip)
		ft_printf("%02x ", e->map[mod_map(pos + i)]);
	ft_printf("\n");
}

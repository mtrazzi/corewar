/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:22:10 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 19:10:44 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	main(int ac, char **av)
{
	t_env	e;

	if (!are_macro_correct())
		return (ft_error_vm(STR_ERR_MACRO));
	ft_init_vm(&e);
	if (parse_arg_vm(ac, av, &e) < 0)
		return (ft_free_vm_env(&e));
	if (parse_all_files(&e) < 0)
		return (ft_free_vm_env(&e));
	if (!e.par.print)
		print_introduction(&e);
	if (init_all_processes(&e) < 0)
		return (ft_free_vm_env(&e));
	if (run_vm(&e) < 0)
		return (ft_free_vm_env(&e));
	if (!(e.par.print || (e.par.dump && e.prc_lst)))
		print_conclusion(&e);
	ft_free_vm_env(&e);
	return (0);
}

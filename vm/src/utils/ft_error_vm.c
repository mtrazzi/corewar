/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:43:59 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/11/04 17:56:42 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define USAGE_1 ("Usage: corewar [-v N | -m][-dump nbr_cycles]")
#define USAGE_2 (" [[-n number] champion1.cor] ...")

int		usage(void)
{
	ft_fprintf(2, "%s%s\n", USAGE_1, USAGE_2);
	return (-1);
}

int		error_usage(char *msg)
{
	ft_fprintf(2, "Error: %s\n", msg);
	ft_fprintf(2, "%s%s\n", USAGE_1, USAGE_2);
	return (-1);
}

int		ft_error(char *msg)
{
	ft_fprintf(2, "Error: %s\n", msg);
	return (-1);
}

int		ft_error_vm(char *error_message)
{
	ft_fprintf(2, "Error: %s\n", error_message);
	return (-1);
}

int		ft_perror_vm(void)
{
	perror("Error");
	return (-1);
}

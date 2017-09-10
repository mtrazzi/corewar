/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:43:59 by mtrazzi           #+#    #+#             */
/*   Updated: 2017/09/10 11:44:04 by mtrazzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

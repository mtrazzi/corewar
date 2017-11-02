/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 19:17:13 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 18:47:19 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_sym(t_sym **sym)
{
	free((*sym)->label);
	free(*sym);
	*sym = NULL;
}

int		clear_asm(t_asm *a)
{
	dll_del_f(&a->syms, del_sym);
	dll_del_f(&a->to_skip_syms, del_sym);
	dll_del(&a->ops);
	return (1);
}

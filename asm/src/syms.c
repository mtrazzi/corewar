/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:51:26 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 15:38:31 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define LABEL_DIFFERENT 0
#define LABEL_EQUAL 1

static int	compare_labels(char *str, int len, char *label)
{
	if (ft_strlen(label) != len)
		return (LABEL_DIFFERENT);
	if (ft_strncmp(label, str, len) == 0)
		return (LABEL_EQUAL);
	return (LABEL_DIFFERENT);
}

static int	cmp_label(t_dll *s, void *data)
{
	if (compare_labels((char *)(*(u_long *)data), (int)(*(u_long *)(data + 8)),
		((t_sym *)(s->content))->label) == LABEL_EQUAL)
		return (0);
	return (1);
}

t_sym		*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms)
{
	u_long	tab[2];
	t_dll	*tmp;

	if (!syms)
		return (NULL);
	tab[0] = (u_long)str;
	tab[1] = (u_long)len;
	tmp = dll_iter_dll(syms, cmp_label, (void *)tab);
	if (tmp)
		return (tmp->content);
	return (NULL);
}

int			get_sym_by_sym(t_dll *dll, void *data)
{
	if (((t_sym *)dll->content)->sym == (u_int)data)
		return (0);
	return (1);
}

u_int		get_next_symbol(t_dll *syms)
{
	t_dll *last;

	last = get_last(syms);
	return (last == NULL ? 0 : ((t_sym *)last->content)->sym + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:51:26 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 19:34:35 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define LABEL_DIFFERENT 0
#define LABEL_EQUAL 1

u_int	get_next_symbol(t_dll *syms)
{
	t_dll *last;

	last = get_last(syms);
	return (last == NULL ? 0 : ((t_sym *)last->content)->sym + 1);
}

int		compare_labels(char *str, int len, char *label)
{
	if (ft_strlen(label) != len)
		return (LABEL_DIFFERENT);
	if (ft_strncmp(label, str, len) == 0)
		return (LABEL_EQUAL);
	return (LABEL_DIFFERENT);
}

/*
int		cmp_label(t_dll *s, void *data)
{
	if (compare_labels((char *)data, (int)(data + 1), ((t_sym *)(s->content))->label)
				== LABEL_EQUAL)
			return (0);
	return (1);
}

t_sym	*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms)
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
*/

t_sym	*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms)
{
	while (syms)//iter?
	{
		if (compare_labels(str, len, ((t_sym *)(syms->content))->label)
				== LABEL_EQUAL)
			return ((t_sym *)(syms->content));
		syms = syms->next;
	}
	return (NULL);
}

t_dll	*create_add_label(char *str, int len, t_dll **syms, u_int symbol)
{
	char	*label;
	t_sym	*new_sym;
	t_dll	*new_dll;

	if ((label = ft_strsub(str, 0, len)) == NULL)
		return (NULL);
	if ((new_sym = create_sym(label, symbol)) == NULL)
	{
		(void)ft_free((void *)&label);
		return (NULL);
	}
	if ((new_dll = dll_new((void*)new_sym)) == NULL)
	{
		(void)(ft_free((void *)&label) * ft_free((void *)&new_sym));
		return (NULL);
	}
	dll_append(syms, new_dll);
	return (new_dll);
}

int		get_sym_by_sym(t_dll *dll, void *data)
{
	if (((t_sym *)dll->content)->sym == (u_int)data)
		return (0);
	return (1);
}

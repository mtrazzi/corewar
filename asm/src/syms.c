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

int		create_add_label(char *str, int len, t_dll **syms, u_int symbol)
{
	char	*label;
	t_sym	*new_sym;
	t_dll	*new_dll;

	if ((label = ft_strsub(str, 0, len)) == NULL)
		return (MAL_ERR);
	if ((new_sym = create_sym(label, symbol)) == NULL)
		return (MAL_ERR * ft_free((void *)&label));
	if ((new_dll = dll_new((void*)new_sym)) == NULL)
		return (MAL_ERR * ft_free((void *)&label) * ft_free((void *)&new_sym));
	dll_append(syms, new_dll);
	return (1);
}

int		get_sym_by_sym(t_dll *dll, void *data)
{
	// ft_printf("TEST3\n");
	if (((t_sym *)dll->content)->sym == (u_int)data)//verify
	{
		// ft_printf("found %u\n", ((t_sym *)dll->content)->sym);
		return (0);
	}
	return (1);
}
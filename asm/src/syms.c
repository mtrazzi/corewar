#include "asm.h"

int		ft_strncmp_modified(char *s1, char *s2, size_t n)
{
	while ((*s1 && *s2) && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	if (n == 1 && *s1 == '\0')//n= 0?
		return (0);
	return (1);
}

// int		cmp_input_label(char *input, char *label)
// {
// 	while ((ft_is_whitespace(*input) == 0 && *input != LABEL_CHAR))
// }


t_sym	*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms)
{
	while (syms)
	{
		if (ft_strncmp_modified(((t_dll)(syms->content))->label, str, len) == 0)
			return ((t_dll)(syms->content));
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
	if ((new_sym == create_sym(label, symbol)) == NULL)
		return (MAL_ERR * ft_free((void *)&label));
	if ((new_dll == dll_new((void*)new_sym)) == NULL)
		return (MAL_ERR * ft_free((void *)&label) * ft_free((void *)&new_sym));
	dll_append(syms, new_dll);
	return (1);
}



#include "asm.h"

int		ft_strncmp_modified(char *s1, char *s2, size_t n)
{
	while (--n && (*s1 && *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (n == 0 && *s1 == '\0')
		return (0);
	return (1);
}

// int		cmp_input_label(char *input, char *label)
// {
// 	while ((ft_is_whitespace(*input) == 0 && *input != LABEL_CHAR))
// }

#define LABEL_DIFFERENT 0
#define LABEL_EQUAL 1

int		compare_labels(char *str, int len, char *label)
{
	if (ft_strlen(label) != len)
		return (LABEL_DIFFERENT);
	if (ft_strncmp(label, str, len) == 0)//--n
		return (LABEL_EQUAL);
	return (LABEL_DIFFERENT);
}


t_sym	*does_label_exist_in_sym_dll(char *str, int len, t_dll *syms)
{
	while (syms)
	{
		if (compare_labels(str, len, ((t_sym *)(syms->content))->label) == LABEL_EQUAL)
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



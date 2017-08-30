
#include "asm.h"

u_int	get_next_symbol2(t_dll *syms)
{
	t_dll *last;

	last = get_last(syms);
	return (last == NULL ? 0 : ((t_sym *)last->content)->sym + 1);
}

int	parse_label_only2(char *line, t_dll **syms, u_int line_number, t_dll **to_skip)//redo
{
	char	*tmp;
	t_sym	*sym_tmp;
	t_dll	*last;

	tmp = line;
	while (line && *line && ft_strchr(LABEL_CHARS, *line))
		line++;
	if (tmp == line || *line != LABEL_CHAR)
		return (IS_NOT_LABEL);
	sym_tmp = does_label_exist_in_sym_dll(tmp, line - tmp, *syms);
	if (sym_tmp != NULL)
	{
		if (create_add_label(tmp, line - tmp, to_skip, 101010) == MAL_ERR)//could avoid malloc label
			return (MAL_ERR);
		last = get_last(*to_skip);//not opti at all
		((t_sym *)last->content)->line_number_parsing_help = line_number;//no protect needed ?
		((t_sym *)last->content)->first_ope = NULL;
		return (1);
	}
	if (create_add_label(tmp, line - tmp, syms, get_next_symbol2(*syms)) == MAL_ERR)
		return (MAL_ERR);
	last = get_last(*syms);//not opti at all
	((t_sym *)last->content)->line_number_parsing_help = line_number;//no protect needed ?
	((t_sym *)last->content)->first_ope = NULL;
	return (1);
}

int		get_labels(t_asm *a)
{
	u_int	line_count = 0;
	char	*line = NULL;
	char	*rem = NULL;
	int		ret;

	while ((ret = get_next_line(a->fd, &line, &rem)) > 0)
	{
		ft_printf("line count: %d %s\n", line_count, line);
		char *tmp = line;
		skip_whitespaces(&tmp);
		if (parse_label_only2(tmp, &a->syms, line_count, &a->to_skip_syms) == MAL_ERR)
			return (ret * ft_free((void *)&line) * ft_free((void *)&rem));
		line_count++;
		ft_free((void *)&line);
	}
	(void)(ft_free((void *)&line) * ft_free((void *)&rem));
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}


/*
int	parse_label_only(char *line, t_dll **syms)//redo
{
	char	*tmp;
	t_sym	*sym_tmp;

	tmp = line;
	while (line && *line && ft_strchr(LABEL_CHARS, *line))
		line++;
	if (*line != LABEL_CHAR)
		return (IS_NOT_LABEL);
	sym_tmp = does_label_exist_in_sym_dll(tmp, line - tmp, *syms);
	if (sym_tmp == NULL && create_add_label(tmp, line - tmp, syms, get_next_symbol(*syms)))
		return (MAL_ERR);
	// sym_tmp->true_sym = 1;
	while (line && *line && ft_is_withespace(*line))
		line++;
	if (*line == '\0')
		return (IS_LABEL_ONLY);
	return (IS_MORE_THAN_LABEL);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:08:27 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/25 14:11:24 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static u_int	get_next_symbol2(t_dll *syms)
{
	t_dll *last;

	last = get_last(syms);
	return (last == NULL ? 0 : ((t_sym *)last->content)->sym + 1);
}

static int	parse_label_only(char *line, t_dll **syms, u_int line_number, t_dll **to_skip)//redo
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
		if ((last = create_add_label(tmp, line - tmp, to_skip, 101010)) == NULL)//could avoid malloc label
			return (MAL_ERR);
		((t_sym *)last->content)->line_number_parsing_help = line_number;
		((t_sym *)last->content)->corresponding_ope = NULL;
		return (1);
	}
	if ((last = create_add_label(tmp, line - tmp, syms, get_next_symbol2(*syms))) == NULL)
		return (MAL_ERR);
	((t_sym *)last->content)->line_number_parsing_help = line_number;
	((t_sym *)last->content)->corresponding_ope = NULL;
	return (1);
}

int		get_labels(t_asm *a)
{
	u_int	line_count = 0;
	char	*line = NULL;
	char	*rem = NULL;
	int		ret;
	char	*tmp;

	while ((ret = get_next_line(a->fd, &line, &rem)) > 0)
	{
		ft_printf("line count: %d %s\n", line_count, line);
		tmp = line;
		skip_whitespaces(&tmp);
		if (parse_label_only(tmp, &a->syms, line_count, &a->to_skip_syms) == MAL_ERR)
			return (ret * ft_free((void *)&line) * ft_free((void *)&rem));
		line_count++;
		ft_free((void *)&line);
	}
	(void)(ft_free((void *)&line) * ft_free((void *)&rem));
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}

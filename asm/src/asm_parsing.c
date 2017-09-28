/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:09:39 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/28 16:34:38 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	init_ope(t_ope *ope)
{
	ope->nb_param = 0;
	ft_bzero(ope->type_param, sizeof(u_int) * MAX_ARGS_NUMBER);
	ft_bzero(ope->params, sizeof(u_int) * MAX_ARGS_NUMBER);
	ope->op_code = MAX_OP;
	ope->size = 0;
	ope->ais = 0;
	ope->op_tab_x = NULL;
	ope->line_nb = 0;
	return (1);
}

static int	parse_op(char **line, t_dll **ops, int line_count, t_asm *a)
{
	t_dll	*new_ope_dll;
	t_ope	ope;
	t_op	*op;
	char	*tmp;

	init_ope(&ope);
	ope.line_nb = line_count;
	tmp = *line;
	tmp = get_next_whitespace(tmp);
	op = does_op_exist_in_op_tab(*line, tmp - *line);
	if (op == NULL)
		return (BAD_OP_NAME);
	ope.op_tab_x = op;
	*line = tmp;
	if (check_params(line, op, &ope, a) != 1)
		return (-1);
	if ((new_ope_dll = create_ope_dll(&ope, op)) == NULL)
		return (-1);
	dll_append(ops, new_ope_dll);
	return (1);
}

static void	skip_labels(char **line, int line_count, t_dll **sym_curr,
						t_dll **to_skip_curr)
{
	if ((*sym_curr) != NULL && line_count ==
			((t_sym *)(*sym_curr)->content)->line_number_parsing_help)
	{
		(*sym_curr) = (*sym_curr)->next;
		skip_to(line, LABEL_CHAR);
		(*line)++;
	}
	else if ((*to_skip_curr) != NULL && line_count ==
				((t_sym *)(*to_skip_curr)->content)->line_number_parsing_help)
	{
		(*to_skip_curr) = (*to_skip_curr)->next;
		skip_to(line, LABEL_CHAR);
		(*line)++;
	}
}

static int	process_line(char **line, t_asm *a, t_parse *p)
{
	int		ret;
	char	*tmp;

	skip_whitespaces(line);
	if (is_com(*line) || **line == '\0')
		return (1);
	skip_labels(line, p->line_count, &p->sym_curr, &p->to_skip_curr);
	skip_whitespaces(line);
	if (is_com(*line) || **line == '\0')
		return (1);
	if (parse_op(line, &a->ops, p->line_count, a) != 1)
		return (-1);
	skip_whitespaces(line);
	if (**line != '\0' && !is_com(*line))
		return (-1);
	return (1);
}

int			parsing(t_asm *a)
{
	char	*line;
	char	*rem;
	int		ret;
	t_parse	p;

	rem = NULL;
	init_t_parse(&p, a);
	if ((ret = get_header(a, &rem, &p)) != 1)
		return (ret * ft_free((void *)&rem));
	line = NULL;
	while ((ret = get_next_line(a->fd, &line, &rem)) > 0)
	{
		p.add_line_start = line;
		p.alc = line;
		if ((ret = process_line(&p.alc, a, &p)) != 1)
			return (ret * error_parse(&p) * free_str(&line) * free_str(&rem));
		p.line_count += 1;
		(void)ft_free((void *)&line);
	}
	(void)(ft_free((void *)&line) * ft_free((void *)&rem));
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}

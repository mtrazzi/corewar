#include "asm.h"

int		init_ope(t_ope *ope)
{
	ope->nb_param = 0;
	ft_bzero(ope->type_param, sizeof(u_int) * MAX_ARGS_NUMBER);//check
	ft_bzero(ope->params, sizeof(u_int) * MAX_ARGS_NUMBER);
	ope->op_code = MAX_OP;
	ope->size = 0;
	ope->address_in_size = 0;
	ope->op_tab_x = NULL;
	ope->line_nb = 0;
	return (1);
}

int parse_op(char **line, t_dll **ops, int line_count, t_asm *a)
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
	ft_printf("{green}op %p{eoc} {%s} [%d]\n", op, tmp, tmp - *line);
	if (op == NULL)
		return (BAD_OP_NAME);
	ope.op_tab_x = op;
	*line = tmp;
	if (check_params(line, op, &ope, a) != 1)
		return (-1);
	if ((new_ope_dll = create_ope_dll(&ope, op)) == NULL)
		return (-1);//MAL_ERR
	dll_append(ops, new_ope_dll);
	return (1);
}

void		skip_labels(char **line, int line_count, t_dll **sym_curr, 
						t_dll **to_skip_curr)
{
	if ((*sym_curr) != NULL && line_count ==
			((t_sym *)(*sym_curr)->content)->line_number_parsing_help)
	{
		sym_str_((t_sym *)(*sym_curr)->content);//
		(*sym_curr) = (*sym_curr)->next;
		skip_to(line, LABEL_CHAR);
		(*line)++;
	}
	else if ((*to_skip_curr) != NULL && line_count ==
				((t_sym *)(*to_skip_curr)->content)->line_number_parsing_help)
	{
		sym_str_((t_sym *)(*to_skip_curr)->content);//
		(*to_skip_curr) = (*to_skip_curr)->next;
		skip_to(line, LABEL_CHAR);
		(*line)++;
	}
}

int	process_line(char **line, t_asm *a, t_parse *p)
{
	int	ret;
	char *tmp;

	skip_whitespaces(line);
	if (is_com(*line) || **line == '\0')
		return (1);
	skip_labels(line, p->line_count, &p->sym_curr, &p->to_skip_curr);
	skip_whitespaces(line);
	if (is_com(*line) || **line == '\0')
		return (1);
	ft_printf("{red}process: {%s}{eoc}\n", *line);
	if (parse_op(line, &a->ops, p->line_count, a) != 1)
		return (-1);
	ft_printf("{red}!!!processed GOOD {%s}{eoc}\n", *line);
	skip_whitespaces(line);
	if (**line != '\0' && !is_com(*line))
		return (-1);
	return (1);
}

void	init_t_parse(t_parse *p, t_asm *a)
{
	p->sym_curr = a->syms;
	p->to_skip_curr = a->to_skip_syms;
	p->line_count = 0;
	p->add_line_start = NULL;
	p->alc = NULL;
}

int		parsing(t_asm *a)
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
		ft_printf("{cyan}line:{eoc} %s\n", line);
		if ((ret = process_line(&p.alc, a, &p)) != 1)
			return (ret * error_parse(&p) * ft_free((void *)&line)
						* ft_free((void *)&rem));
	 	p.line_count += 1;
		(void)ft_free((void *)&line);
	}
	(void)(ft_free((void *)&line) * ft_free((void *)&rem));
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}
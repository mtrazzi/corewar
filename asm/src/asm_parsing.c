#include "asm.h"

int		free_lr(char **l, char **r)
{
	if (l && *l)
	{
		free(*l);
		*l = NULL;
	}
	if (r && *r)
	{
		free(*r);
		*r = NULL;
	}
	return (1);
}

int	ft_is_withespace(char c)
{
	return (c ==  ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r');
}


u_int	get_next_symbol(t_dll *syms)
{
	t_dll *last;

	last = get_last(syms);
	return (last == NULL ? 0 : ((t_sym *)last->content)->sym + 1);
}

int	is_com(char *str)
{
	if (str && (*str == COMMENT_CHAR || *str == COMMENT_CHAR2))
		return (1);
	return (0);
}



#define BAD_OP_NAME -20//BAD_OP_CODE


int		init_ope(t_ope *ope)
{
	ope->nb_param = 0;
	ft_bzero(ope->type_param, sizeof(u_int) * MAX_ARGS_NUMBER);
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
	t_ope	ope;//init?
	t_op	*op;
	char	*tmp;

	op = NULL;//useless
	init_ope(&ope);
	ope.line_nb = line_count;
	tmp = *line;
	*line = get_next_whitespace(*line);
	op = does_op_exist_in_op_tab(tmp, *line - tmp);
	ft_printf("{green}op %p{eoc} {%s} [%d]\n", op, *line, *line-tmp);
	if (op == NULL)
		return (BAD_OP_NAME);
	ope.op_tab_x = op;
	if (check_params(line, op, &ope, a) != 1)
		return (-1);
	if ((new_ope_dll = create_ope_dll(&ope, op)) == NULL)
		return (-1);//MAL_ERR
	dll_append(ops, new_ope_dll);
	return (1);
}

int	process_line(char *line, t_asm *a, u_int line_count, t_dll **sym_current, t_dll **to_skip_curr)
{
	int	ret;
	char *tmp;

	skip_whitespaces(&line);
	if (!*line)
		return (1);
	if ((*sym_current) != NULL && line_count == ((t_sym *)(*sym_current)->content)->line_number_parsing_help)
	{//line begin with label
		sym_str_((t_sym *)(*sym_current)->content);
		(*sym_current) = (*sym_current)->next;
		skip_to(&line, LABEL_CHAR);
		line++;
	}
	else if ((*to_skip_curr) != NULL && line_count == ((t_sym *)(*to_skip_curr)->content)->line_number_parsing_help)
	{
		sym_str_((t_sym *)(*to_skip_curr)->content);
		(*to_skip_curr) = (*to_skip_curr)->next;
		skip_to(&line, LABEL_CHAR);
		line++;
	}
	skip_whitespaces(&line);
	if (is_com(line) || *line == '\0')
		return (1);
	ft_printf("{red}process: {%s}{eoc}\n", line);
	if (parse_op(&line, &a->ops, line_count, a) != 1)
		return (-1);
	ft_printf("{red}!!!processed GOOD {%s}{eoc}\n", line);
	skip_whitespaces(&line);
	if (*line && !is_com(line))
		return (-1);
	return (1);
}

//support multi line .comment?
int		parsing(t_asm *a)
{
	u_int		line_count;
	char	*line = NULL;
	char	*rem = NULL;
	int		ret;
	t_dll	*sym_current = a->syms;
	t_dll	*to_skip_curr = a->to_skip_syms;

	line_count = 0;

	if ((ret = get_header(a, &line_count, &rem)) != 1)
		return (ret * ft_free((void *)&rem));
	ft_printf("header name: {%s}\n", a->header.prog_name);
	ft_printf("header comment: {%s}\n", a->header.comment);
	while ((ret = get_next_line(a->fd, &line, &rem)) > 0)
	{
		ft_printf("{cyan}line:{eoc} %s\n", line);
		if ((ret = process_line(line, a, line_count, &sym_current, &to_skip_curr)) != 1)
			return (ret);
		line_count++;
		//frees
	}
	//frees
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}
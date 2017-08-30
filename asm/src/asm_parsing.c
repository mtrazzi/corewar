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


int parse_op(char *line, t_dll **ops)
{
	t_op	*op;
	char	*tmp;

	tmp = line;
	while (line && *line && !ft_is_withespace(*line))
		line++;
	op = does_op_exist_in_op_tab(tmp, line - tmp);
	if (op == NULL)
		return (BAD_OP_NAME);
	// else if ()//checkparams!
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
		skip_whitespaces(&line);
	}
	else if ((*to_skip_curr) != NULL && line_count == ((t_sym *)(*to_skip_curr)->content)->line_number_parsing_help)
	{
		sym_str_((t_sym *)(*to_skip_curr)->content);
		(*to_skip_curr) = (*to_skip_curr)->next;
		skip_to(&line, LABEL_CHAR);
		line++;
		skip_whitespaces(&line);
	}
	ft_printf("{red}process: {%s}{eoc}\n", line);
	if (is_com(line) || *line == '\0')//ou empty line
		return (1);
	// 	return (1);
	//skip whitespacesonly lines
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
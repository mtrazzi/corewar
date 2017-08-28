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

int	ft_is_withespace(char a)
{
	return (c ==  ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r');
}


#define GNL_ERR -100
#define IS_NOT_LABEL -10
#define IS_LABEL_ONLY 11
#define IS_MORE_THAN_LABEL 12

u_int	get_next_symbol(t_dll *syms)
{
	t_dll *last;

	last = get_last(syms);
	return (last == NULL ? 0, last->sym + 1);
}

int	is_com(char *str)
{
	// while (str && ft_is_withespace(*str))
	// 	str++;
	if (str && *str == COMMENT_CHAR)
		return (1);
	return (0);
}

int	parse_label_only(char *line, t_dll **syms)
{
	char	*tmp;
	t_sym	*sym_tmp;

	tmp = line;
	while (line && ft_strchr(LABEL_CHARS, *line))
		line++;
	if (*line != LABEL_CHAR)
		return (IS_NOT_LABEL);
	sym_tmp = does_label_exist_in_sym_dll(tmp, line - tmp, *syms);
	if (sym_tmp == NULL && create_add_label(tmp, line - tmp, syms, get_next_symbol(syms)))
		return (MAL_ERR);
	sym_tmp->true_sym = 1;
	while (line && ft_is_withespace(*line))
		line++;
	if (*line == '\0')
		return (IS_LABEL_ONLY);
	return (IS_MORE_THAN_LABEL);
}

int parse_op(char *line, t_dll **ops)
{
	char	*tmp;

	tmp = line;
	while (line && !ft_is_withespace(*line))
		line++;
	
}

int	process_line(char *line, t_asm *a)
{
	char *tmp;

	while (line && ft_is_withespace(*line))
		line++;
	if (is_com(line))
		return (1);
	if ((ret = parse_label_only(line, &a->syms)) == MAL_ERR)
		return (MAL_ERR);
	else if (ret == IS_LABEL_ONLY)
		return (1);
	else if (ret == IS_MORE_THAN_LABEL || ret == IS_NOT_LABEL)
		
	// 	return (1);
	//skip whitespacesonly lines
	return (1);
}

int		parsing(t_asm *a)
{
	int		line_count;
	char	*line = NULL;
	char	*rem = NULL;
	int		ret;

	line_count = 0;

	//get_headers_params
	while ((ret = get_next_line(a->fd, &line, &rem)) > 0)
	{
		if ((ret = process_line(line, a)) != 1)
			return (ret);
	}
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}
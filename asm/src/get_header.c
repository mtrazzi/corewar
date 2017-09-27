#include "asm.h"

int		parse_comment(char **str, t_asm *a, u_int *parsed)
{
	char *tmp;

	if (parsed[1] == 1)
		return (-1);
	*str += ft_strlen(COMMENT_CMD_STRING);
	skip_whitespaces(str);
	if (**str != '"')
		return (-1);
	tmp = get_next(*str + 1, '"');
	if (*tmp == '\0')
		return (-1);
	else if (tmp - (*str + 1) > COMMENT_LENGTH)//check ca
		return (-1);
	else
		ft_strncpy(a->header.comment, *str + 1, tmp - (*str + 1));
	*str = tmp + 1;
	skip_whitespaces(str);
	if (**str != '\0' && !is_com(*str))
		return (-1);
	parsed[1] = 1;
	return (1);
}

int		parse_name(char **str, t_asm *a, u_int *parsed)
{
	char *tmp;

	if (parsed[0] == 1)
		return (-1);
	*str += ft_strlen(NAME_CMD_STRING);
	skip_whitespaces(str);
	if (**str != '"')
		return (-1);
	tmp = get_next(*str + 1, '"');
	if (*tmp == '\0')
		return (-1);
	else if (tmp - (*str + 1) > PROG_NAME_LENGTH)//check ca
		return (-1);
	else
		ft_strncpy(a->header.prog_name, *str + 1, tmp - (*str + 1));
	*str = tmp + 1;
	skip_whitespaces(str);
	if (**str != '\0' && !is_com(*str))
		return (-1);
	parsed[0] = 1;
	return (1);
}

int	 parse_name_or_comment(char **str, t_asm *a, u_int *parsed)
{
	int i;

	if (ft_strncmp(*str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		return (parse_name(str, a, parsed));
	else if (ft_strncmp(*str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
		return (parse_comment(str, a, parsed));
	else
		return (-1);
	return (1);
}

int		get_header(t_asm *a, char **rem, t_parse *p)
{
	char	*line;
	int		ret;
	u_int	parsed[2];

	parsed[0] = 0;
	parsed[1] = 0;
	line = NULL;
	while ((ret = get_next_line(a->fd, &line, rem)) > 0)
	{
		p->add_line_start = line;
		p->alc = line;
		skip_whitespaces(&p->alc);
		if (is_com(p->alc) || *p->alc == '\0')
			;
		else if (parse_name_or_comment(&p->alc, a, parsed) != 1)
			return (-1 * ft_free((void *)&line) * error_parse(p));
		p->line_count += 1;
		if (parsed[0] == 1 && parsed[1] == 1)
			break ;
		ft_free((void *)&line);
	}
	(void)ft_free((void *)&line);
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}
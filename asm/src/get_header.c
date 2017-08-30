#include "asm.h"

int		parse_comment(char *str, t_asm *a)
{
	char *tmp;

	if (a->parsed_com == 1)
		return (-1);
	str += ft_strlen(COMMENT_CMD_STRING);
	skip_whitespaces(&str);
	if (*str != '"')
		return (-1);
	tmp = get_next(str + 1, '"');
	if (tmp == '\0')
		return (-1);
	else if (tmp - str > COMMENT_LENGTH)//check ca
		return (-1);
	else
		ft_strncpy(a->header.comment, str, tmp - str);
	str = tmp + 1;
	skip_whitespaces(&str);
	if (*str != '\0' && !is_com(str))
		return (-1);
	a->parsed_com = 1;
	return (1);
}

int		parse_name(char *str, t_asm *a)
{
	char *tmp;

	if (a->parsed_name == 1)
		return (-1);
	str += ft_strlen(NAME_CMD_STRING);
	skip_whitespaces(&str);
	if (*str != '"')
		return (-1);
	tmp = get_next(str + 1, '"');
	if (tmp == '\0')
		return (-1);
	else if (tmp - str > PROG_NAME_LENGTH)//check ca
		return (-1);
	else
		ft_strncpy(a->header.prog_name, str, tmp - str);
	str = tmp + 1;
	skip_whitespaces(&str);
	if (*str != '\0' && !is_com(str))
		return (-1);
	a->parsed_name = 1;
	return (1);
}

int	 parse_name_or_comment(char *str, t_asm *a)
{
	int i;

	if (ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		return (parse_name(str, a));
	else if (ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
		return (parse_comment(str, a));
	else
		return (-1);
	return (1);
}

int		get_header(t_asm *a, u_int *line_count, char **rem)
{
	char	*line = NULL;
	int		ret;

	u_int	mask = 0;
	while ((ret = get_next_line(a->fd, &line, rem)) > 0)
	{
		*line_count += 1;
		char *tmp = line;
		skip_whitespaces(&tmp);
		if (is_com(tmp) || *tmp == '\0')
			;
		else if (parse_name_or_comment(tmp, a) != 1)
			return (-1 * ft_free((void *)&line));
		if (a->parsed_name == 1 && a->parsed_com == 1)
			break ;
		ft_free((void *)&line);
	}
	(void)ft_free((void *)&line);
	if (ret < 0)
		return (GNL_ERR);
	return (1);
}
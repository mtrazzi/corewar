/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:41:52 by pkirsch           #+#    #+#             */
/*   Updated: 2017/09/29 15:33:24 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	header_error(t_parse *p, int parsed)
{
	if ((parsed & 1) == 0)
		ft_fprintf(2, "Error: missing name\n");
	if ((parsed & 2) == 0)
		ft_fprintf(2, "Error: missing comment\n");
	error_parse(p);
	return (1);
}

static int	parse_comment(char **str, t_asm *a, u_int *parsed)
{
	char *tmp;

	if (*parsed & 2)
		return (-1);
	*str += ft_strlen(COMMENT_CMD_STRING);
	skip_whitespaces(str);
	if (**str != '"')
		return (-1);
	tmp = get_next(*str + 1, '"');
	if (*tmp == '\0')
		return (-1);
	else if (tmp - (*str + 1) > COMMENT_LENGTH)
		return (-1);
	else
		ft_strncpy(a->header.comment, *str + 1, tmp - (*str + 1));
	*str = tmp + 1;
	skip_whitespaces(str);
	if (**str != '\0' && !is_com(*str))
		return (-1);
	*parsed |= 2;
	return (1);
}

static int	parse_name(char **str, t_asm *a, u_int *parsed)
{
	char *tmp;

	if (*parsed & 1)
		return (-1);
	*str += ft_strlen(NAME_CMD_STRING);
	skip_whitespaces(str);
	if (**str != '"')
		return (-1);
	tmp = get_next(*str + 1, '"');
	if (*tmp == '\0')
		return (-1);
	else if (tmp - (*str + 1) > PROG_NAME_LENGTH)
		return (-1);
	else
		ft_strncpy(a->header.prog_name, *str + 1, tmp - (*str + 1));
	*str = tmp + 1;
	skip_whitespaces(str);
	if (**str != '\0' && !is_com(*str))
		return (-1);
	*parsed |= 1;
	return (1);
}

static int	parse_name_or_comment(char **str, t_asm *a, u_int *parsed)
{
	if (ft_strncmp(*str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		return (parse_name(str, a, parsed));
	else if (ft_strncmp(*str, COMMENT_CMD_STRING,
							ft_strlen(COMMENT_CMD_STRING)) == 0)
		return (parse_comment(str, a, parsed));
	else
		return (-1);
}

int			get_header(t_asm *a, char **rem, t_parse *p)
{
	char	*line;
	int		ret;
	u_int	parsed;

	parsed = 0;
	line = NULL;
	while (parsed != 3 && (ret = get_next_line(a->fd, &line, rem)) > 0)
	{
		p->add_line_start = line;
		p->alc = line;
		skip_whitespaces(&p->alc);
		if (is_com(p->alc) || *p->alc == '\0')
			;
		else if (parse_name_or_comment(&p->alc, a, &parsed) != 1)
			return (-1 * ft_free((void *)&line) * header_error(p, parsed));
		p->line_count += 1;
		(void)ft_free((void *)&line);
	}
	(void)ft_free((void *)&line);
	if (ret < 0)
		return (GNL_ERR);
	if (ret == 0 && parsed != 3)
		return (-1 * header_error(p, parsed));
	return (1);
}

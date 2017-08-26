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

#define GNL_ERR -100

int	is_com(char *str)
{
	if (str && str[0] == COMMENT_CHAR)
		return (1);
	return (0);
}

int	process_line(char *line, t_asm *a)
{
	if (is_com(line))
		return (1);
	// if (is_label(line))
	// 	return (1);
	return (1);
}

int		parsing(t_asm *a)
{
	char	*line = NULL;
	char	*rem = NULL;
	int		ret;


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
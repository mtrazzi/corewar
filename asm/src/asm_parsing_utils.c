#include "asm.h"

void	skip_whitespaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && ft_is_withespace(**str))
		(*str)++;
}

void	skip_to_whitespaces(char **str)//or end
{
	if (!str || !*str)
		return ;
	while (**str && !ft_is_withespace(**str))
		(*str)++;
}

char	*get_next_separator(char *str)//or end
{
	if (!str)
		return (NULL);
	while (*str && *str != SEPARATOR_CHAR)
		str++;
	return (str);
}

char	*get_next_whitespace(char *str)//or end
{
	if (!str)
		return (NULL);
	while (*str && !ft_is_withespace(*str))
		str++;
	return (str);
}

void	skip_to(char **str, char c)//or end //return -1 if not encountered before end?
{
	if (!str || !*str)
		return ;
	while (**str && **str != c)
		(*str)++;
}

char	*get_next(char *str, char c)//or end
{
	if (!str)
		return (NULL);
	while (*str && *str != c)
		str++;
	return (str);
}

int	ft_atoi_mod(const char *str)
{
	int		i;
	long	number;
	int		is_negative;

	i = 0;
	number = 0;
	is_negative = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' ||
		str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		is_negative = (str[i] == '-') ? -1 : 1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - 48);
	number *= is_negative;
	return ((int)number);
}

int	is_com(char *str)
{
	if (str && (*str == COMMENT_CHAR || *str == COMMENT_CHAR2))
		return (1);
	return (0);
}

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

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

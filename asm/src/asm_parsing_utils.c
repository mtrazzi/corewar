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

#include "asm.h"

/*
** Ignore whitespace at end of line
** Ignore comments at end of line
** Ignore whitespaces at beginning of line
** Ignore comments
*/

static	int		ft_is_whtspc(char c)
{
	printf("%c\n", c);
	return (c == '\t' || c == ' ' || c == '\r' || c == '\n' || c == '\v');
}

static	char	*ft_process_begin_line(char *line)
{
	while (ft_is_whtspc(*line))
		line++;
	if (*line == '#')
		return (NULL);
	return (line);
}

char	*ft_process_line(char *line) //returns NULL if string is comment of whitespace, 
{									 //line without whitespace and comments otherwise
	char *result;

	result = ft_process_begin_line(line);
	return (result);
}

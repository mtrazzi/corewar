#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	printf("start:\n\t%s, %s\n", s1, s2);
	while ((*s1 && *s2) && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
		printf("\t%s, %s\n", s1, s2);
	}
	printf("end:\n\t%s, %s\n", s1, s2);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		compare_op_names(char *str, int len, char *op_name)
{
	if (strlen(op_name) != len)
		return (-1);
	if (ft_strncmp(op_name, str, len) == 0)
		return (1);
	return (-1);
}

int	ft_is_withespace(char c)
{
	return (c ==  ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r');
}

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

char	*get_next_whitespace(char *str)//or end
{
	if (!str)
		return (NULL);
	while (*str && !ft_is_withespace(*str))
		str++;
	return (str);
}

int main(int argc, char const *argv[])
{
	char *a = "\t\f\n  \r\tasdjhfgksdajfgh\n.\n.\t.\nasdfsidhsf\f\t\n";
	char *tmp = NULL;

	printf("{%s}\n", a);
	skip_whitespaces(&a);
	printf("[%s]\n", a);
	skip_whitespaces(&a);
	printf("(%s)\n", a);

	tmp = get_next_whitespace(a);
	printf("_%s_\n", tmp);
	printf("_%s_\n", a);
	skip_to_whitespaces(&a);
	printf("+%s+\n", a);
	return 0;
}

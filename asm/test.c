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

int main(int argc, char const *argv[])
{
	char *a = "balei";
	char *x = "balei\t";

	char *tmp = x;
	while (*tmp != '\t')
		tmp++;
	printf("RESULT: %s, %s, %d\n", a, x, ft_strncmp(a, x, tmp - x));
	printf("RESULT: %s, %s, %d\n", a, x, compare_op_names(x, tmp - x, a));
	return 0;
}

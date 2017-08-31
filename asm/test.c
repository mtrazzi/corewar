#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>

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

u_int	convert(u_int to_rev)
{
	u_int tmp;

	tmp = 0;
	tmp = (0x000000ff & to_rev) << 24;
	tmp |= (0x0000ff00 & to_rev) << 8;
	tmp |= (0x00ff0000 & to_rev) >> 8;
	tmp |= (0xff000000 & to_rev) >> 24;
	return (tmp);
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

#define REG_NUMBER				16

int		get_reg(char *str)
{
	u_int	res;
	char	*tmp;

	str++;
	tmp = str;
	while (*str && isdigit(*str))
		str++;
	if (tmp - str == 0)
		return (-1);
	res = ft_atoi_mod(tmp);
	if (res == 0 || res > REG_NUMBER)
		return (-1);
	printf("res _%u_\n", res);
	return (1);
}

#define NAME_CMD_STRING			".name"
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

	printf("%08x\n", convert(0x0083f3ff));
	printf("atoi %ld\n", (long)(u_int)ft_atoi_mod("-4294967"));
	printf("atoi %ld\n", (long)(u_int)atoi("-4294967"));

	printf("%d\n", ft_strncmp(".namfasdasdas", NAME_CMD_STRING, strlen(NAME_CMD_STRING)));
	printf("{%c}\n", NAME_CMD_STRING[strlen(NAME_CMD_STRING)]);

	printf("get_reg: %d\n", get_reg("r16a5a"));
	return 0;
}

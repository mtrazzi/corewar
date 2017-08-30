#include "vm.h"

int		ft_error_vm(char *error_message)
{
	ft_fprintf(2, "Error: %s\n", error_message);
	return (-1);
}

int		ft_perror_vm(void)
{
	perror("Error");
	return (-1);
}

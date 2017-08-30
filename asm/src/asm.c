#include "asm.h"

int	init_header(header_t *h)
{
	h->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(h->prog_name, PROG_NAME_LENGTH + 1);
	h->prog_size = 0;
	ft_bzero(h->comment, COMMENT_LENGTH + 1);
	return (1);
}

int	init_asm(t_asm *a)
{
	a->parsed_name = 0;
	a->parsed_com = 0;
	a->syms = NULL;
	a->ops = NULL;
	a->to_skip_syms = NULL;
	init_header(&a->header);
	a->fd = 0;
	return (1);
}

int main(int ac, char **av)
{
	t_asm a;

	a.fd = open(av[1], O_RDONLY);
	if (a.fd < 0)
		return (ft_printf("COULD NOT OPEN %s\n", av[1]));
	get_labels(&a);
	ft_printf("DONE\n");
	sym_dll_print("parsed labels\n", a.syms);
	sym_dll_print("to_skip labels\n", a.to_skip_syms);

	close(a.fd);
	a.fd = open(av[1], O_RDONLY);
	parsing(&a);
	return (0);
}


	//t_asm e;

	// ft_init_asm(&e);
	// if (ac != 2)
	// 	return (ft_error_asm(&e, "not the valid number of arguments. Expected one."));
	// if (ft_file_to_lst_asm(&e, av[1]) < 0)
	// 	return (-1);
	// if (ft_update_fd_asm(&e, av[1]) < 0)
	// 	return (ft_error_asm(&e, "error opening file."));
	// ft_free_asm_env(&e);

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

	init_asm(&a);
	a.fd = open(av[1], O_RDONLY);
	if (a.fd < 0)
		return (ft_printf("Can't read source file %s\n", av[1]));
	init_g_op();
	get_labels(&a);
	ft_printf("DONE\n");
	sym_dll_print("parsed labels\n", a.syms);
	sym_dll_print("to_skip labels\n", a.to_skip_syms);

	close(a.fd);
	a.fd = open(av[1], O_RDONLY);
	if (parsing(&a) != 1)//if error, free lists
		return (-1);
	close(a.fd);

	sym_dll_print("{On_blue}parsed labels{eoc}\n", a.syms);
	sym_dll_print("{On_blue}to_skip labels{eoc}\n", a.to_skip_syms);
	dll_print_f("{On_blue}ops{eoc}\n", a.ops, ope_str_);
	prep(&a);
	sym_dll_print("{On_red}parsed labels{eoc}\n", a.syms);
	dll_print_f("{On_blue}ops OCP{eoc}\n", a.ops, ope_str_);
	//ft_printf("magic {%u}\nname {%s}\ncomment {%s}\n", a.header.magic, a.header.prog_name, a.header.comment);
	update_fd_asm(&a, av[1]);
	//SAUT DE LIGNE A LA FIN DU FICHIER->PQ????
	//4294967291->-5
	print_header(&a);
	print_cmds(&a);
	return (0);
}

//what if programme size > MAX allowed?


	//t_asm e;

	// ft_init_asm(&e);
	// if (ac != 2)
	// 	return (ft_error_asm(&e, "not the valid number of arguments. Expected one."));
	// if (ft_file_to_lst_asm(&e, av[1]) < 0)
	// 	return (-1);
	// if (ft_update_fd_asm(&e, av[1]) < 0)
	// 	return (ft_error_asm(&e, "error opening file."));
	// ft_free_asm_env(&e);

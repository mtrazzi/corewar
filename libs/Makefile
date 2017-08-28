
NAME = libs

all : $(NAME)	

$(NAME):
	@$(MAKE) -C libft libft.a
	@$(MAKE) -C dllst dllst.a
	@$(MAKE) -C ft_printf libftprintf.a

clean:
	@$(MAKE) -C libft clean
	@$(MAKE) -C dllst clean
	@$(MAKE) -C ft_printf clean

fclean:
	@$(MAKE) -C libft fclean
	@$(MAKE) -C dllst fclean
	@$(MAKE) -C ft_printf fclean	

re: fclean all

.PHONY: all fclean clean re

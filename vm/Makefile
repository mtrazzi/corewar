
CC = gcc

CFLAGS = -Wall -Wextra

NAME = corewar

SRC = 	ft_error_vm.c		\
		ft_free_vm.c		\
		ft_init_vm.c		\
		parse_arg.c			\
		parse_file_vm.c		\
		vm.c				\
		str_utils.c			\
		str_utils2.c		\
		ft_print_utils.c	\
		init_process.c		\
		one_cycle.c			\
		do_process.c		\
		run_vm.c			\
		op_utils.c			\
		op_utils2.c			\
		check_params.c		\
		global_utils.c		\
		check_header.c

SRC +=	live.c				\
		ld.c				\
		st.c				\
		add.c				\
		sub.c				\
		and.c				\
		or.c				\
		xor.c				\
		zjmp.c				\
		ldi.c				\
		sti.c				\
		fork.c				\
		lld.c				\
		lldi.c				\
		lfork.c				\
		aff.c

SRC +=	mul.c				\
		death.c				\
		nand.c				\
		jump.c				\
		bomb.c				\
		copy.c

SRC +=	ncurses.c

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include:src/op
IFLAGS = -I include
HEADERS = vm.h op.h

DLLST_PATH = ../libs/dllst
DLLST = $(DLLST_PATH)/dllst.a
IFLAGS += -I $(DLLST_PATH)/include

LIBFT_PATH = ../libs/libft
LIBFT = $(LIBFT_PATH)/libft.a
IFLAGS += -I $(LIBFT_PATH)/include

FT_PRINTF_PATH = ../libs/ft_printf
FT_PRINTF = $(FT_PRINTF_PATH)/libftprintf.a
IFLAGS += -I $(FT_PRINTF_PATH)/include

LIBS = $(DLLST) $(LIBFT) $(FT_PRINTF)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building $(NAME)..."
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lncurses $(LIBS)
	@echo "\033[3;94m!$(NAME) built!\033[0m"

$(OBJ_PATH)%.o: %.c $(HEADERS) $(LIBS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS)

$(LIBS):
	@$(MAKE) -C ../libs all

clean:
	@$(MAKE) -C ../libs clean
	rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C ../libs fclean
	@/bin/rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re


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
		parse_arg2.c		\
		opts.c				\
		global_utils.c		\
		check_header.c		\
		parse_champions.c	\
		opts_utils.c

ifeq ($(OPTIONS_OP), yes)
SRC += g_op_tab_more.c
DFLAG = -D OPTIONS_OP
else
SRC +=g_op_tab.c
DFLAG =
endif


SRC += malloc_wrapper.c

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
##condition! put in folder
SRC +=	mul.c				\
		death.c				\
		nand.c				\
		jump.c				\
		copy.c				\
		bomberman.c

SRC +=	ncurses.c			\
		ncurses_controls.c	\
		ncurses_style.c		\
		ncurses_infos.c		\
		ncurses_stats.c		\
		ncurses_helpers.c

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include:src/op
IFLAGS = -I include
HEADERS = vm.h op.h print_ncurses.h

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
	@echo "\033[0;31mPUT BACK \033[0;32mALL\033[0;31m FLAGS!!!!!!!!!\033[0m"
	@echo "\033[0;31mPUT BACK \033[0;32mALL\033[0;31m FLAGS!!!!!!!!!\033[0m"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lncurses $(LIBS) $(DFLAG)
	@echo "\033[0;31mPUT BACK \033[0;32mALL\033[0;31m FLAGS!!!!!!!!!\033[0m"
	@echo "\033[0;31mPUT BACK \033[0;32mALL\033[0;31m FLAGS!!!!!!!!!\033[0m"
	@echo "\033[3;94m!$(NAME) built!\033[0m"

$(OBJ_PATH)%.o: %.c $(HEADERS) $(LIBS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS) $(DFLAG)

$(LIBS):
	@$(MAKE) -C ../libs all

clean:
	@$(MAKE) -C ../libs clean
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C ../libs fclean
	@/bin/rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re

CC = gcc

ifeq ($(DEBUG),yes)
    CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
else
    CFLAGS = -Wall -Wextra -Werror
endif
#-O2

NAME = asm

SRC_UTIL = 

SRC_DLLST = dll_create.c dll_push_pop.c dll_size.c dll_transfer.c \
			dll_del.c dll_get.c dll_utils.c dll_iter.c

SRC = $(SRC_UTIL) $(SRC_DLLST) main.c creates.c print_room.c \
		parsing_lem_in.c parsing_rename.c get_next_line.c \
		print_tube.c prep_graph.c edmonds.c print_combo.c \
		parsing_tube.c parsing_room.c razdal_mo_eraz.c \
		check_antshill.c parsing_antshill.c exit.c \
		queue.c trace_back.c cmp_utils.c

OBJ_F = $(SRC:.c=.o)
OBJ = $(addprefix ./obj/, $(OBJ_F))

PYTHON_OBJ = common.pyc visualizor.pyc
PYTHON = $(addprefix ./constructor/, $(PYTHON_OBJ))

VPATH = src/utils:src:src/dllst:include
IFLAGS = -I include -I ft_printf/includes
HEADERS = dll.h lem_in.h util.h

PRINTF_FILE		=	libftprintf.a
PRINTF_PATH		=	./ft_printf/
PRINTF			=	$(addprefix $(PRINTF_PATH), $(PRINTF_FILE))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(PRINTF) $(CFLAGS)

./obj/%.o: %.c $(HEADERS) $(PRINTF)
	@mkdir -p obj
	$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS)

$(PRINTF):
	@$(MAKE) -C $(PRINTF_PATH) libftprintf.a

clean:
	@$(MAKE) -C $(PRINTF_PATH) clean
	rm -rf ./obj
	@rm -rf $(PYTHON)
	@rm -rf $(NAME).dSYM

fclean: clean
	@$(MAKE) -C $(PRINTF_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

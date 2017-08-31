
CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = asm

SRC = asm.c \
		creates.c \
		syms.c \
		asm_parsing.c \
		ops.c \
		asm_parsing_utils.c \
		get_labels.c \
		visu.c \
		get_header.c \
		prep.c

#op.c

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include
IFLAGS = -I include
HEADERS = asm.h op.h

DLLST_PATH = ../libs/dllst
DLLST = $(DLLST_PATH)/dllst.a
IFLAGS += -I $(DLLST_PATH)/include

LIBFT_PATH = ../libs/libft
LIBFT = $(LIBFT_PATH)/libft.a
IFLAGS += -I $(LIBFT_PATH)/include

PRINTF_PATH = ../libs/ft_printf
PRINTF = $(PRINTF_PATH)/libftprintf.a
IFLAGS += -I $(PRINTF_PATH)/include

LIBS = $(DLLST) $(LIBFT) $(PRINTF)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;31mPUT BACK FLAGS!!!!!!!!!\033[0m"
	@echo "\033[0;31mPUT BACK FLAGS!!!!!!!!!\033[0m"
	$(CC) -o $(NAME) $(OBJ) $(LIBS)
	@echo "\033[0;31mPUT BACK FLAGS!!!!!!!!!\033[0m"
	@echo "\033[0;31mPUT BACK FLAGS!!!!!!!!!\033[0m"
#$(CFLAGS)

$(OBJ_PATH)%.o: %.c $(HEADERS) $(LIBS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(IFLAGS)
#$(CFLAGS)

$(LIBS):
	@$(MAKE) -C ../libs all

#ifeq ($TARGET, NAME)
#clean libs ? necessary only in project Makefile?
clean:
	@$(MAKE) -C ../libs clean
	rm -rf $(OBJ_PATH)

fclean: clean
	@$(MAKE) -C ../libs fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

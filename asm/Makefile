
CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = asm

SRC = asm.c \
		creates.c \
		syms.c \
		asm_parsing.c

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

LIBS = DLLST LIBFT

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)

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
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

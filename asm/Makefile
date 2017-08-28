
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
HEADERS = asm.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

$(OBJ_PATH)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

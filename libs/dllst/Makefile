
CC = gcc
AR = ar rc
RAN = ranlib

NAME = dllst.a

CFLAGS = -Wall -Wextra -Werror

SRC = dll_create.c \
		dll_push_pop.c \
		dll_size.c \
		dll_transfer.c \
		dll_del.c \
		dll_get.c \
		dll_utils.c \
		dll_iter.c

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include

IFLAGS = -I include
HEADERS = dll.h

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	$(RAN) $(NAME)

$(OBJ_PATH)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

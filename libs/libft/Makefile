
NAME = libft.a

CC = gcc
AR = ar rc
RAN = ranlib

CFLAGS = -Wall -Wextra -Werror

SRC = 

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include

IFLAGS = -I include
HEADERS = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	$(RAN) $(NAME)

./obj/%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
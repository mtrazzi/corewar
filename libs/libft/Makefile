
NAME = libft.a

CC = gcc
AR = ar rc
RAN = ranlib

CFLAGS = -Wall -Wextra -Werror

SRC = ft_bzero.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strsub.c \
		ft_free.c

SRC += get_next_line.c

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include

IFLAGS = -I include
HEADERS = libft.h get_next_line.h

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

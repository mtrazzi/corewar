# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/29 17:38:30 by pkirsch           #+#    #+#              #
#    Updated: 2017/11/06 19:17:22 by pkirsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

ifeq ($(DEBUG), yes)
CFLAGS = -g3 #-fsanitize=address
else ifeq ($(NOFLAGS), yes)
CFLAGS =
else
CFLAGS = -Wall -Wextra -Werror
endif

NAME = asm

SRC = asm.c					\
		error_output.c		\
		file_handling.c		\
		str_utils.c

SRC += endian_utils.c		\
		output_bytecode.c

SRC += asm_parsing.c 		\
		asm_parsing_utils.c \
		get_header.c 		\
		get_labels.c 		\
		parse_op.c 			\
		parse_op_utils.c

SRC += prep.c 		\
		size.c

SRC += creates.c	\
		del.c		\
		op.c		\
		syms.c

DFLAG =

ifeq ($(OPTIONS_OP), yes)
SRC += g_op_tab_more.c
DFLAG += -D OPTIONS_OP
else
SRC += g_op_tab.c
endif

ifeq ($(COMPARE), yes)
DFLAG += -D COMPARE
endif

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:include:src/parsing:src/prep:src/output_bytecode:src/op_sym
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

EXISTS := $(shell sh anti_collisions.sh op=$(OPTIONS_OP) name=$(NAME) cmp=$(COMPARE))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIBS) $(CFLAGS) $(DFLAG)

$(OBJ_PATH)%.o: %.c $(HEADERS) $(LIBS)
	@mkdir -p $(OBJ_PATH)
	@(echo "\033[32m assembly :[ \033[31m\t\c")
	@(echo "$@ \033[32m]\033[0m \033[0K")
	@$(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS) $(DFLAG)
	@(echo "\033[2F")


$(LIBS):
	$(MAKE) -C ../libs all

clean:
	@/bin/rm -rf .flags
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

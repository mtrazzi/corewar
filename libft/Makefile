# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrazzi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/27 16:05:15 by mtrazzi           #+#    #+#              #
#    Updated: 2017/08/14 19:02:14 by mtrazzi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC = libft.h get_next_line.h

MKF = Makefile

SRC =	ft_atoi.c				\
		ft_itoa.c				\
		ft_bzero.c				\
		ft_isalnum.c			\
		ft_isalpha.c			\
		ft_isascii.c			\
		ft_isdigit.c			\
		ft_isprint.c			\
		ft_memalloc.c			\
		ft_memccpy.c			\
		ft_memchr.c				\
		ft_memcmp.c				\
		ft_memcpy.c				\
		ft_memdel.c				\
		ft_memmove.c			\
		ft_memset.c				\
		ft_putchar.c			\
		ft_putchar_fd.c			\
		ft_putendl.c			\
		ft_putendl_fd.c			\
		ft_putnbr.c				\
		ft_putnbr_fd.c			\
		ft_putstr.c				\
		ft_putstr_fd.c			\
		ft_strcat.c				\
		ft_strchr.c				\
		ft_strclr.c				\
		ft_strcmp.c				\
		ft_strcpy.c				\
		ft_strdel.c				\
		ft_strdup.c				\
		ft_strequ.c				\
		ft_striter.c			\
		ft_striteri.c			\
		ft_strjoin.c			\
		ft_strlcat.c			\
		ft_strlen.c				\
		ft_strmap.c				\
		ft_strmapi.c			\
		ft_strncat.c			\
		ft_strncmp.c			\
		ft_strncpy.c			\
		ft_strnequ.c			\
		ft_strnew.c				\
		ft_strnstr.c			\
		ft_strrchr.c			\
		ft_strsplit.c			\
		ft_strstr.c				\
		ft_strsub.c				\
		ft_strtrim.c			\
		ft_tolower.c			\
		ft_toupper.c			\
		ft_max.c				\
		ft_min.c				\
		ft_free.c				\
		ft_parse_utils.c		\
		ft_pfutils.c			\
		ft_pfassign_type.c		\
		ft_pfchange.c			\
		ft_pfconv_d.c			\
	  	ft_pffree.c				\
	  	ft_pfinit.c				\
	  	ft_pfinsert.c			\
	  	ft_pfnext_conversion.c	\
	  	ft_pfparse.c			\
	  	ft_pfparse_opt.c		\
	  	ft_pfprintf.c 			\
	  	ft_pfvalue.c			\
	  	ft_pfconv_s.c			\
	  	ft_pfprint_s.c			\
	  	ft_pfprint_c.c			\
	  	ft_pfprint_uni.c		\
		ft_lstadd.c				\
		ft_lstdel.c				\
		ft_lstdelone.c			\
		ft_lstiter.c			\
		ft_lstmap.c				\
		ft_lstnew.c				\
		get_next_line.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(OBJ) $(INC) $(MKF)
	@echo "Building $(NAME)..."
	@gcc -c -Wall -Wextra -I$(INC) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[3;94m!$(NAME) built!\033[0m"
	
clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, $(NAME)

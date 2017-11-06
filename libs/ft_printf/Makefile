
NAME = libftprintf.a

CC	= gcc
AR	= ar rc
RAN	= ranlib

CFLAGS = -O2 -Wall -Wextra -Werror

SRC += 	cvt_d.c \
		cvt_o.c \
		cvt_u.c \
		cvt_x.c \
		cvt_p.c \
		cvt_c.c \
		cvt_lc.c \
		cvt_s.c \
		cvt_ls.c \
		cvt_b.c \
		cvt_percent.c \
		cvt_inv.c \
		cvt_f.c \
		cvt_n.c \
		uni.c \
		uni_util.c

SRC +=	get_format.c \
		get_format_util.c \
		color.c \
		get_options.c

SRC +=	ft_printf.c \
		ft_sprintf.c

SRC +=	ft_putd.c \
		ft_puts.c \
		ft_puto.c \
		ft_putx.c \
		ft_putls.c \
		ft_putp.c \
		ft_putu.c \
		ft_putf.c \
		ft_putls_util.c \
		ft_put_util.c

SRC +=	ft_isdigit.c \
		ft_iterative_power_long_double.c \
		ft_strlen.c \
		ft_memset.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strchr.c

OBJ_FILES = $(SRC:.c=.o)
OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

VPATH = src:src/cvt:src/primary:src/print:src/put:src/util:include

IFLAGS = -I include
HEADERS = cvt.h ft_color.h ft_printf.h ft_put.h primary.h util.h

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@$(RAN) $(NAME)

$(OBJ_PATH)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_PATH)
	@(echo "\033[32m printf :[ \033[31m\t\c")
	@(echo "$@ \033[32m]\033[0m \033[0K")
	@($(CC) -c $< -o $@ $(IFLAGS) $(CFLAGS))
	@(echo "\033[2F")

clean :
	@/bin/rm -rf $(OBJ_PATH)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

.PHONY: re fclean clean all

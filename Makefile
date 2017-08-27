NAME_1			=	asm

NAME_2			=	corewar

CC				=	clang

FLAGS			=	-Wall -Wextra

MKF				=	Makefile

#--------------------------------------------------------------------------------
# PATHS
#--------------------------------------------------------------------------------

SRC_PATH_1		=	./asm_src/

SRC_PATH_2		=	./vm/

INC_PATH		=	./includes/

OBJ_PATH		=	./obj/

LIB_PATH		=	./libft/

#--------------------------------------------------------------------------------
# SRC
#--------------------------------------------------------------------------------

SRC_FILES_1		=	asm.c					\
					ft_free_asm.c			\
					ft_init_asm.c			\
					ft_print_lst_utils.c	\
					ft_read_asm.c			\
					ft_error_asm.c			\
					ft_header_asm.c			\
					ft_new_fd_asm.c			\
					ft_endian_utils.c		\
					ft_type.c				\
					ft_process_line.c		\
					ft_size_cmd.c			\
					ft_write_cmd.c

SRC_FILES_2		=	vm.c

SRC_1			=	$(addprefix $(SRC_PATH_1), $(SRC_FILES_1))

SRC_2			=	$(addprefix $(SRC_PATH_2), $(SRC_FILES_2))

#--------------------------------------------------------------------------------
# OBJ
#--------------------------------------------------------------------------------

OBJ_FILES_1		=	$(SRC_FILES_1:.c=.o)

OBJ_1			=	$(addprefix $(OBJ_PATH), $(OBJ_FILES_1))

OBJ_FILES_2		=	$(SRC_FILES_2:.c=.o)

OBJ_2			=	$(addprefix $(OBJ_PATH), $(OBJ_FILES_2))

#--------------------------------------------------------------------------------
# INC
#--------------------------------------------------------------------------------

INC				=	$(addprefix -I, $(INC_PATH))

HEADER_FILES	=	libft.h				\
					get_next_line.h		\
					asm.h				\
					dll.h				\
					op.h

HEADERS			=	$(addprefix $(INC_PATH), $(HEADERS_FILES))

#--------------------------------------------------------------------------------
# DEPENDENCIES
#--------------------------------------------------------------------------------

LIB_FILE		=	libft.a

LIB				=	$(addprefix $(LIB_PATH), $(LIB_FILE))

#--------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------

all: $(NAME_1) $(NAME_2)

$(NAME_1): $(LIB) $(OBJ_1) $(MKF) $(HEADERS)
	@echo "Building $(NAME_1)..."
	$(CC) $(CFLAGS) $(LIB) $(OBJ_1) -o $@
	@echo "\033[3;94m!$(NAME_1) built!\033[0m"

$(NAME_2): $(LIB) $(OBJ_2) $(MKF) $(HEADERS)
	@echo "Building $(NAME_2)..."
	$(CC) $(CFLAGS) $(LIB) $(OBJ_2) -o $@
	@echo "\033[3;94m!$(NAME_2) built!\033[0m"

$(LIB):
	@$(MAKE) -C $(LIB_PATH) $(LIB_FILE)

$(OBJ_PATH)%.o: $(SRC_PATH_1)%.c $(HEADERS) $(LIB)
	@mkdir -p obj
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PATH_2)%.c $(HEADERS) $(LIB)
	@mkdir -p obj
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LIB_PATH) fclean
	@/bin/rm -f $(OBJ_1)
	@/bin/rm -f $(OBJ_2)

fclean: clean
	@/bin/rm -f $(NAME_1)
	@/bin/rm -f $(NAME_2)

re: fclean all

linux: $(LIB)
	@echo "Building $(NAME_1)..."
	$(CC) $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(NAME_1)
	@echo "\033[3;94m!$(NAME_1) built!\033[0m"
	@echo "Building $(NAME_2)..."
	$(CC) $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(NAME_2)
	@echo "\033[3;94m!$(NAME_2) built!\033[0m"

norme: fclean
	norminette $(SRC_1)
	norminette $(LIB_PATH)
	norminette $(INC_PATH)	

.PHONY: all, clean, fclean, re, norme

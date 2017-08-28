#ifndef ASM_H

# define ASM_H
# include "libft.h"
# include "dll.h"
# include "op.h"
# include <sys/types.h>

# define LABEL_NO	0
# define LABEL_2	2
# define LABEL_4	4

#define LIVE		0x0001
#define LD			0x0002
#define ST	 		0x0004
#define	ADD 		0x0008
#define SUB 		0x0010
#define AND 		0x0020
#define OR			0x0040
#define XOR			0x0080
#define ZJMP 		0x0100
#define LDI			0x0200
#define STI			0x0400
#define FORK		0x0800
#define LLD			0x1000
#define LLDI		0x2000
#define LFORK		0x4000
#define AFF			0x8000

#define IS_LABEL_NO 0b1000000000011100	
#define	IS_LABEL_2	0b0110111100000000	
#define	IS_LABEL_4	0b0001000011100011	
#define IS_PCB		0b1011011011111110	

# define PAR_SIZE_REG 1
# define PAR_SIZE_IND 2

typedef struct s_op		t_op;
typedef struct s_asm	t_asm;
typedef struct s_param	t_param;
typedef struct s_ope	t_ope;
typedef struct s_sym	t_sym;

struct			s_asm
{
	t_dll		*syms;
	t_dll		*ops;		//liste de lignes du .s
	header_t	*header;	//header au debut du .cor
	int			fd;			//file descriptor du .cor
};

struct			s_param
{
	t_arg_type	type;
	u_int		n;
	u_int		sym;
};

struct			s_ope
{
	u_int		sym;//char *label
	u_int		op_code;
	u_int		nb_par;
	t_param		p1;
	t_param		p2;
	t_param		p3;
	u_int		size;
	//t_op			*op_tab_x;
};

struct			s_sym
{
	char		*label;
	u_int		sym;
	char		true_sym;
};


struct			s_op
{
	char	*name;
	u_int	nb_param;
	//type param
	u_int	op_code;
	u_int	nb_cycles;
	char	*full_name;
	u_int	ocp;
	u_int	last_arg;
};

struct			s_typparam
{
	
};

#define MAX_OP

t_op    g_op_tab[17] =
{
/*
**  {"nom", 	nb_param,	{type des param}, 										opcode, nb_cycles,	"nom_complet", 		OCP 
*/
    {"live", 	1,			{T_DIR}, 												1, 		10, 		"alive", 			0, 0},
    {"ld", 		2, 			{T_DIR | T_IND, T_REG}, 								2, 		5,	 		"load", 			1, 0},
    {"st", 		2, 			{T_REG, T_IND | T_REG}, 								3, 		5, 			"store", 			1, 0},
    {"add", 	3, 			{T_REG, T_REG, T_REG}, 									4, 		10, 		"addition", 		1, 0},
    {"sub", 	3, 			{T_REG, T_REG, T_REG}, 									5, 		10, 		"soustraction", 	1, 0},
    {"and", 	3, 			{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6,			"et",				1, 0},
    {"or", 		3, 			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6,			"ou", 				1, 0},
    {"xor", 	3, 			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6,			"ou", 				1, 0},
    {"zjmp", 	1, 			{T_DIR}, 												9, 		20, 		"jump if zero", 	0, 1},
    {"ldi", 	3, 			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10,		25,			"load index", 		1, 1},
    {"sti", 	3, 			{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11,		25,			"store index", 		1, 1},
    {"fork", 	1, 			{T_DIR}, 												12,		800, 		"fork", 			0, 1},
    {"lld", 	2, 			{T_DIR | T_IND, T_REG}, 								13, 	10, 		"long load", 		1, 0},
    {"lldi", 	3, 			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,		50,			"long load index",	1, 1},
    {"lfork", 	1, 			{T_DIR}, 												15,		1000, 		"long fork", 		0, 1},
    {"aff", 	1, 			{T_REG}, 												16,		2, 			"aff", 				1, 0},
    {0, 		0, 			{0}, 													0, 		0, 			0, 					0, 0}
};


#endif

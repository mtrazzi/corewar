#include "asm.h"


t_op	g_op_tab[MAX_OP] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
{"mul", 3, {T_REG, T_REG, T_REG}, 17, 10, "mul", 1, 0},
{"injury", 1, {T_DIR}, 18, 10, "injury", 0, 0},
{"nand", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 19, 6, "nand r1, r2, r3   not(r1&r2) -> r3", 1, 0},
{"jmp", 1, {T_DIR}, 20, 100, "jump anyway", 0, 1},
{"bomb", 1, {T_DIR}, 21, 400, "throws bomb and jump anyway", 0, 1},
{"copy", 3, {T_REG, T_REG, T_REG}, 22, 100, "r1 -> r2 and r1 -> r3", 1, 0},
{"kamikaze", 1, {T_DIR}, 23, 100, "kamikazeeee", 0, 1},

	{0, 0, {0}, 0, 0, 0, 0, 0}
};


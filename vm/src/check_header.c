#include "vm.h"

int		are_macro_correct(void)
{
	return (IND_SIZE == 2 && REG_SIZE == 4 && DIR_SIZE == 4 &&
	REG_CODE == 1 && DIR_CODE == 2 && IND_CODE == 3 &&
	MAX_ARGS_NUMBER == 4 && MAX_PLAYERS == 4 &&
	(MEM_SIZE == (4 * 1024)) && IDX_MOD == (MEM_SIZE / 8) &&
	CHAMP_MAX_SIZE == (MEM_SIZE / 6) &&
	REG_NUMBER >= 16 && REG_NUMBER <= 100 &&
	(CYCLE_TO_DIE > (10 * CYCLE_DELTA)) && CYCLE_TO_DIE < 10000 &&
	CYCLE_DELTA >= 10 && CYCLE_DELTA <= 100 &&
	NBR_LIVE > 10 && NBR_LIVE <= 100 &&
	MAX_CHECKS >= 10 && MAX_CHECKS <= 100 &&
	T_REG == 1 && T_DIR == 2 && T_IND == 4 && T_LAB == 8 &&
	PROG_NAME_LENGTH == 128 && COMMENT_LENGTH == 2048 && NB_OP >= 16 &&
	NB_OP <= 22);
}

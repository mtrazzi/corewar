

if cyc_left == 0:
	actually_do_op()
	op = get_next_op()
		if op_is_valid():
			cyc_left = op.cycles
else:
	cyc_left--;

#load params
while cycle_is_ok():
	if cyc_since_beg != 0:
		process_exec_op_update_cyc_left()
	process_load_op()


def wrapper_delone(t_dll):
	if TA_CONDITION:
		dll_delone()

foreach_tmp(lst, wrapper)

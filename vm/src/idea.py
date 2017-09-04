

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




def do_one_cycle():
	process_load_op()
	process_exec_op_update_cyc_left():

def process_load_op(e, prc):
	if prc->cyc_left != 0:
		return (0)
	prc->op_code = read()
	if prc->op_code.bad_op_code() == True:
		prc->op_code = NB_OP + 1
	prc->cyc_left = nb_cycles

def process_exec_op_update_cyc_left(e, prc):
	
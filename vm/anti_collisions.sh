#!/bin/bash

if [[ -f ./obj/g_op_tab_more.o  ]] && [[ "$1" == "" ]]; then
	rm -rf obj
	rm -rf corewar
elif [[ -f ./obj/g_op_tab.o ]] && [[ "$1" == "yes" ]]; then
	rm -rf obj
	rm -rf corewar
fi

#!/bin/sh

CHAMP_PATH="./resources/champions_staff/champ/"
CHAMP_LIST=""

while test ${#} -gt 0
do
	./asm/asm $CHAMP_PATH$1.s
	CHAMP_LIST+="$CHAMP_PATH$1.cor "
	shift
done
./vm/corewar -m $CHAMP_LIST

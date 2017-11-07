#!/bin/bash

RED="\033[0;31m"
BLUE="\033[0;34m"
GREEN="\033[0;32m"
EOC="\033[0m"

function _test {

/bin/rm -rf $1.cor
/bin/rm -rf $1.corr

../resources/asm $1.s > /dev/null
./asm $1.s > /dev/null

PARAM=$1
NAME=${PARAM##*/}
xxd $1.cor > cor_$NAME
xxd	$1.corr > corr_$NAME

/bin/rm -rf diff_$1
if [[ $2 == "-diff" ]]
then
	echo ""
	diff -y --speed-large-files -s corr_$NAME cor_$NAME
else
	RESULT=$(diff --speed-large-files -s corr_$NAME cor_$NAME)
fi

/bin/rm -rf cor_$NAME corr_$NAME
/bin/rm -rf $1.cor
/bin/rm -rf $1.corr

if [[ $2 == "-diff" ]]
then
	exit
fi

if [[ $RESULT == *"identical"* ]]
then
	echo "\033[0;32m OK\033[0m"
else
	echo "\033[0;31m ERROR\033[0m"
fi
}

DIFF=""

if [[ $1 == "-1" ]]
then
	FILES=$2
	DIFF="-diff"
else
	FILES=$1/*
fi

count=0
for f in $FILES
do
	if [[ $f == *".s" ]]
	then
		echo "$f\c"
		f=${f%.s}
		_test $f $DIFF
		let "count=$count + 1"
	fi
done
echo "\t\t\033[0;36mTested $count files\033[0m"

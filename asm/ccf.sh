#!/bin/sh
/bin/rm -rf ../resources/champions_staff/champ/$1.cor
/bin/rm -rf ../resources/champions_staff/champ/$1.corr

../resources/asm ../resources/champions_staff/champ/$1.s
./asm ../resources/champions_staff/champ/$1.s > /dev/null

xxd ../resources/champions_staff/champ/$1.cor > cor_$1
xxd	../resources/champions_staff/champ/$1.corr > corr_$1

/bin/rm -rf diff_$1
diff -y --speed-large-files -s corr_$1 cor_$1 #> diff_$1
#cat diff_$1
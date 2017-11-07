
! [[ -f ./asm ]] && echo "\033[31mAsm not compiled!\033[0m" && exit -1

FILES=`find . -name '*.s'`

for f in $FILES
do
	echo "\033[32mCompiling \033[0m$f \c"
	CHAMP="$(./asm $f 2>&1)"
	if [[ $CHAMP == *"riting"* ]]; then
		echo "\033[32mOK\033[0m"
	else
		echo "\033[31m$CHAMP\033[0m"
	fi
done
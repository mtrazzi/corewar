export CHAMP="../resources/champions_staff/$1.s"
../resources/asm $CHAMP
../resources/corewar -v 4 ../resources/champions_staff/$1.cor > zaz.log
./corewar -v ../resources/champions_staff/$1.cor > my.log
diff my.log zaz.log

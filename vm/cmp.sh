export CHAMP="../resources/champions_staff/$1.s"
../resources/asm $CHAMP
../resources/corewar -v 31 ../resources/champions_staff/$1.cor > zaz.log
./corewar -v 31 ../resources/champions_staff/$1.cor > my.log
diff -y --speed-large-files my.log zaz.log

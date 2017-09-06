export CHAMP="../resources/champions_staff/$1.s"
../resources/asm $CHAMP
echo "writing zaz.log"
../resources/corewar -v 4 ../resources/champions_staff/$1.cor > zaz.log # ../resources/champions_staff/$1.cor > zaz.log
echo "writing my.log"
./corewar -v 4 ../resources/champions_staff/$1.cor > my.log #../resources/champions_staff/$1.cor > my.log
echo "doing the diff"
diff --speed-large-files my.log zaz.log > diff.log

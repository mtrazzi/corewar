CHAMP="../resources/jino_corewar/champ/$1.s"
../resources/asm $CHAMP
echo "executing zaz corewar > zaz.log"
../resources/corewar -v 31 ../resources/jino_corewar/champ/$1.cor > zaz.log # ../resources/champions_staff/$1.cor > zaz.log
echo "executing my corewar > my.log"
./corewar -v 31 ../resources/jino_corewar/champ/$1.cor > my.log #../resources/champions_staff/$1.cor > my.log
#echo "doing the diff"
diff -y --speed-large-files my.log zaz.log

CHAMP="../resources/champions_staff/champ/$1"
../resources/asm $CHAMP.s
echo "executing zaz corewar > zaz$1.log"
../resources/corewar -v 31 $CHAMP.cor > log/zaz$1.log # ../resources/champions_staff/$1.cor > zaz.log
echo "executing my corewar > my$1.log"
./corewar -v 31 $CHAMP.cor > log/my$1.log #../resources/champions_staff/$1.cor > my.log
echo "doing the normal diff"
diff -c -s --speed-large-files log/my$1.log log/zaz$1.log > log/diff$1.log
echo "\033[0;32m\c"
cat log/diff$1.log
echo "\033[0m\c"
#/bin/rm log/my$1.log log/zaz$1.log log/diff$1.log

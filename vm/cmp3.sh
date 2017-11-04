# CHAMP="../resources/champions_staff/$1.s"
# ../resources/asm $CHAMP
echo "executing zaz corewar > zaz3.log"
../resources/corewar -v 31 ../resources/champions_staff/toto.cor ../resources/champions_staff/champ/helltrain.cor ../resources/champions_staff/champ/helltrain.cor > zaz3.log
echo "executing my corewar > my3.log"
./corewar -v 31 ../resources/champions_staff/toto.cor ../resources/champions_staff/champ/helltrain.cor ../resources/champions_staff/champ/helltrain.cor  > my3.log
echo "doing the diff"
# diff -y --speed-large-files my3.log zaz3.log
diff -s --speed-large-files my3.log zaz3.log
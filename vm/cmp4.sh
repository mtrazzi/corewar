# CHAMP="../resources/champions_staff/$1.s"
# ../resources/asm $CHAMP
echo "executing zaz corewar > zaz4.log"
../resources/corewar -v 31 ../resources/champions_staff/champ/Asombra.cor ../resources/champions_staff/champ/helltrain.cor ../resources/champions_staff/champ/Asombra.cor ../resources/champions_staff/champ/helltrain.cor > zaz4.log # ../resources/champions_staff/champ/$1.cor > zaz.log
echo "executing my corewar > my4.log"
./corewar -v 31 ../resources/champions_staff/champ/Asombra.cor ../resources/champions_staff/champ/helltrain.cor ../resources/champions_staff/champ/Asombra.cor ../resources/champions_staff/champ/helltrain.cor  > my4.log #../resources/champions_staff/champ/$1.cor > my.log
echo "doing the diff"
# diff -y --speed-large-files my4.log zaz4.log
diff -s --speed-large-files my4.log zaz4.log
CHAMP="../resources/champions_staff/champ/$1"
MY_FILE="log/my$1dump$2.log"
ZAZ_FILE="log/zaz$1dump$2.log"
DIFF_LOG="log/diff$1dump$2.log"
COL_DIFF_LOG="log/columm_diff$1dump$2.log"

../resources/asm $CHAMP.s

echo "executing ../resources/corewar -d $2 $CHAMP.cor"
../resources/corewar -d $2 $CHAMP.cor > $ZAZ_FILE
echo "executing ./corewar -dump $2 $CHAMP.cor > log/zaz$1dump$2.log"
./corewar -dump $2 $CHAMP.cor > $MY_FILE
echo "doing the normal diff"
diff -c -s --speed-large-files $MY_FILE $ZAZ_FILE > $DIFF_LOG
#less $DIFF_LOG
#echo "doing the column diff"
#diff -y --speed-large-files $MY_FILE $ZAZ_FILE > $COL_DIFF_LOG
cat $DIFF_LOG

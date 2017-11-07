ASM_PATH='../../compiler'
CHAMP_PATH='../champions_staff/champ'

while read line
do
	$ASM_PATH/asm  $CHAMP_PATH/$line.s
done < final_list

while read line
do
	sh mtr.sh $line
done < final_list

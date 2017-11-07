
mkdir -p log

while read line
do
	sh diff_log.sh $line
done < final_list

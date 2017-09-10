while read line
do
	sh dump.sh $line 50
	sh dump.sh $line 500
	sh dump.sh $line 5000
	sh dump.sh $line 50000
done < final_list

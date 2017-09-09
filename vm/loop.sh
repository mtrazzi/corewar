a=$2
while [ $a -lt $3 ]
do
	echo "##### >> $a << #####"
	sh dump.sh $1 $a
	a=`expr $a + 1`
	echo '\n'
done


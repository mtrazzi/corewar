
while read line
do
	echo "$line"
	if [[ $line == *"It is now cycle 5600"* ]]
	then
		exit
	fi
done < "${1:-/dev/stdin}"

##./corewar -v 31 ../resources/champions_staff/champ/Asombra.cor ../resources/champions_staff/champ/helltrain.cor ../resources/champions_staff/champ/Asombra.cor ../resources/champions_staff/champ/helltrain.cor

while read line
do
  echo "test1 said: $line"
  if [[ $line == *"toto"* ]]
  	then
  		exit
  fi
done < "${1:-/dev/stdin}"

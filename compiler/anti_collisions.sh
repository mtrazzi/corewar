#!/bin/bash

FLAGS=".flags"
CONTENT=`[[ -f $FLAGS ]] && cat $FLAGS || echo ""`

OP=`echo $CONTENT | awk '{print $1}'`
CMP=`echo $CONTENT | awk '{print $2}'`

if [[ "$1" != "$OP" ]] || [[ "$3" != "$CMP" ]]; then
	rm -rf obj
	rm -rf "$2"
fi
echo "$1 $3" > $FLAGS

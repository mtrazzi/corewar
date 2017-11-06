#!/bin/bash

FLAGS=".flags"
CONTENT=`[[ -f $FLAGS ]] && cat $FLAGS || echo ""`

OP=`echo $CONTENT | awk '{print $1}'`

if [[ "$1" != "$OP" ]]; then
	rm -rf obj
	rm -rf "$2"
fi
echo "$1" > $FLAGS

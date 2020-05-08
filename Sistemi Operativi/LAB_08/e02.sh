#!/bin/bash

if [ $# -eq 1 ] ; then
    file=$1
else
    read file
fi

if [ ! -f $file ] ; then
    echo "$1 non e' un file"
    exit 1
fi

tmp="$$.tmp"

while read line ; do
    echo $line | wc -c
done < $file > $tmp

max_char=$(sort -n -k1,1 $tmp | tail -n 1)
lines=$(wc -l $tmp | cut -d " " -f 1)

rm $tmp

echo "Caratteri riga piu' lunga: $max_char"
echo "Numero righe: $lines"

exit 0


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

let index=0
strings=()
counts=()
for string in $(cat $file) ; do
    let i=0
    for stringA in ${strings[*]} ; do
        if [ $string = $stringA ] ; then
            let counts[$i]=counts[$i]+1
            break
        fi
        let i=i+1
    done
    if [ $i -eq ${#strings[*]} ] ; then
        strings[$index]=$string
        let counts[$index]=1
        let index=index+1
    fi
done

let i=0
for string in ${strings[*]} ; do
    echo "$string ${counts[$i]}"
    let i=i+1
done

exit 0


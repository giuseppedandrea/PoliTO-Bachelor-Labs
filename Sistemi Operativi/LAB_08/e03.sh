#!/bin/bash

if [ $# -eq 1 ] ; then
    dir=$1
else
    read dir
fi

if [ ! -d $dir ] ; then
    echo "$1 non e' un direttorio"
    exit 1
fi

for file in $(ls $dir) ; do
    new_file=$(echo $file | tr "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz")
    if [ $file != $new_file ] ; then
        mv $dir/$file $dir/$new_file
    fi
done

exit 0


#!/bin/bash

if [ $# -ne 2 ] ; then
    echo "usage: $0 <nome processo> <intervallo tempo>"
    exit 1
fi

let count=0
while true ; do
    status=$(ps -el | grep -e "$1" | tr -s " " | cut -d " " -f 2)
    if [ $status = "Z" ] ; then
        let count=count+1
        if [ $count -eq 5 ] ; then
            pid=$(ps -el | grep -e "$1" | tr -s " " | cut -d " " -f 4)
            kill -9 $pid
            exit 0
        fi
    else
        let count=0
    fi

    sleep $2
done

exit 0

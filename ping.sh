#!/bin/bash
if [ "$#" -ne 1  ] ; then
	echo "Usage :./ping.sh [/24 network address]"
	echo "Example : ./ping.sh 172.16.20.0"
exit

fi

prefix=$(echo $1 | cut -d "." -f 1-3)
for addr in $(seq 1  254); do
	ping -c 1 $prefix.$addr | grep "bytes from" | cut -d " " -f 4 | cut -d ":" -f 1  &
done
wait

#!/bin/bash 
if [ "$#" -ne 1  ] ; then
	echo "Usage :./ping.sh [/24 network address]"
	echo "Example : ./ping.sh 172.16.20.0"
exit

fi
pre=$(echo $1 | cut -d "." -f 1-2)
for ad in $(seq 0 8) ; do 
		for addr in $(seq 1  254); do
			( ping -c 1 $pre.$ad.$addr  &> /dev/null ;
			if [ $? -eq 0 ] ;  then
			echo $pre.$ad.$addr is alive
			fi ) &
		done
done
#wait

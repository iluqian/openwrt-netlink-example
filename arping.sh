#!/bin/bash
if [ "$#" -ne 1 ];then
	echo "Usgae ./arping.sh [interface]"
	echo "Example ./arping.sh eth0"
exit

fi
interface=$1
prefix=$(ifconfig $interface | grep "netmask" | awk -F " " '{print $2}' | cut -d "." -f 1-3 )
for addr in $(seq 1 254); do
	arping -c 1 $prefix.$addr | grep "reply from" | (cut -d " " -f 4-5) &
done
wait 

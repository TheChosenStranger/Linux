#!/bin/sh
newData=1
while true;
do
	sleep 1
	findUSB=$(ls /media/pi/ | grep -c "")
	if [ $findUSB -ne 0 ]
	then
		if [ $newData -ne 0 ]
		then	
			biosPath=$(find /media/pi -name BIOS)
			romsPath=$(find /media/pi -name roms)
			cp -dr $biosPath /home/pi/RetroPie
			#echo "copied roms"
			cp -dr $romsPath /home/pi/RetroPie
			newData=0
		fi
	else
		newData=1
	fi
done

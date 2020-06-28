#!/bin/sh
hdmi_flag=0
hdmi_temp=255
firstTime=1
while :
do
	sleep 1
	hdmi_flag=$( tvservice -v 7 -n | grep -c "device_name" )
	echo $hdmi_flag
	if [ $hdmi_flag -ne 0 ]; then
		sudo cp /home/pi/habd/hdmiAudio /home/pi/.asoundrc
		echo "hdmi" > /home/pi/habd/sh8al
		firsTime=0
	else
		if[ $firstTime -ne 0 ]; then
			sudo cp /home/pi/habd/hdmiAudio /home/pi/.asoundrc
		else	
			sudo cp /home/pi/habd/speakerAudio /home/pi/.asoundrc
		fi
		echo "headphone" > /home/pi/habd/sh8al
	fi
	
done

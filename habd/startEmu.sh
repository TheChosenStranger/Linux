#!/bin/sh
sleep 2
sudo systemctl start lightdm
echo 1 > /home/pi/habd/fstarted
aplay /home/pi/RetroPie/splashscreens/smb_powerup.wav
lxterminal --command=emulationstation

#!/bin/sh

set -u
set -e

# Add a console on tty1
if [ -e ${TARGET_DIR}/etc/inittab ]; then
    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
	sed -i '/GENERIC_SERIAL/a\
tty1::respawn:/sbin/getty -L  tty1 0 vt100 # HDMI console' ${TARGET_DIR}/etc/inittab
fi

################# Enabling Wifi #######################################
if [ ! -d "${TARGET_DIR}/etc/wpa_supplicant" ]; then
	sudo mkdir ${TARGET_DIR}/etc/wpa_supplicant
fi
sudo chmod 777 ${TARGET_DIR}/etc/wpa_supplicant
if [ ! -f "${TARGET_DIR}/etc/wpa_supplicant/wpa_supplicant.conf" ]; then
	sudo touch ${TARGET_DIR}/etc/wpa_supplicant/wpa_supplicant.conf
fi
sudo chmod 777 ${TARGET_DIR}/etc/wpa_supplicant/wpa_supplicant.conf
sudo cp package/busybox/S10mdev ${TARGET_DIR}/etc/init.d/S10mdev
sudo chmod 777 ${TARGET_DIR}/etc/init.d/S10mdev
sudo cp package/busybox/mdev.conf ${TARGET_DIR}/etc/mdev.conf
sudo chmod 777 ${TARGET_DIR}/etc/mdev.conf


cat > output/target/etc/wpa_supplicant/wpa_supplicant.conf << EOL
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US
network={
        ssid="Blue"
        key_mgmt=WPA-PSK
        psk="23121973janet"
     
}
EOL

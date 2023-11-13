#!/bin/bash

DEVICE="/dev/mmcblk0"
MOUNTPOINT="/media/cdrom"

if [ "$UID" -ne 0 ]
then
	echo "Please run as root."
	exit 1
fi

# Get ISO
wget https://downloads.raspberrypi.org/raspbian_lite_latest -O raspbian-buster-lite.zip
unzip -p raspbian-buster-lite.zip > raspbian-buster-lite.img && rm raspbian-buster-lite.zip

# Copy ISO to Device
dd if=raspbian-buster-lite.img of=${DEVICE} bs=4M

# Configuration
mount ${DEVICE}p1 ${MOUNTPOINT}
if [ $? -eq 0 ]
then
	touch ${MOUNTPOINT}/ssh
	cat << EOF > ${MOUNTPOINT}/wpa_supplicant.conf
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
network={
  ssid="yourssid"
  psk="passphrase"
}
EOF
	umount ${MOUNTPOINT}
fi

echo "Done."

exit 0

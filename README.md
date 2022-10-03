https://wiki.volkszaehler.org/hardware/channels/heating_control/gastherme_junkers_can_bus

/boot/config.txt :
dtparam=spi=on
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25
dtoverlay=spi-bcm2835-overlay

apt-get install can-utils

ip link set can0 up type can bitrate 10000 listen-only on

ifconfig can0

candump can0


gcc gastherme.c -o gastherme -lmosquitto


Thanks to
https://github.com/craigpeacock/CAN-Examples
https://github.com/Johannes4Linux/libmosquitto_examples


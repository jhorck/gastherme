Interface for Junkers/Bosch Gastherme with Heatronic 2<br>
The BM1 CAN module is required with a TA250/TA270 controller<br>
All data from the CAN bus is published to a local MQTT broker<br>

See also:<br>
https://wiki.volkszaehler.org/hardware/channels/heating_control/gastherme_junkers_can_bus

/boot/config.txt:<br>
dtparam=spi=on<br>
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25<br>
dtoverlay=spi-bcm2835-overlay<br>

apt-get install can-utils

ip link set can0 up type can bitrate 10000 listen-only on

ifconfig can0

candump can0



Thanks to:<br>
https://github.com/craigpeacock/CAN-Examples<br>
https://github.com/Johannes4Linux/libmosquitto_examples


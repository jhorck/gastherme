// https://github.com/craigpeacock/CAN-Examples
// https://github.com/Johannes4Linux/libmosquitto_examples

// gcc gastherme.c -o gastherme -lmosquitto


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mosquitto.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

void parse(struct can_frame *frame, struct mosquitto *mosq) {
	int i, len, max_len=20, res=MOSQ_ERR_SUCCESS;
	int16_t data;
	char buf[max_len];
	switch(frame->can_id) {
		case 0x200:
			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
			//printf("max Vorlauftemperatur       : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/vorlauftemperatur/max", len, buf, 0, false);
			break;
		case 0x201:
			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
			//printf("ist Vorlauftemperatur       : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/vorlauftemperatur/ist", len, buf, 0, false);
			break;
		case 0x202:
//			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
//			//printf("max Warmwassertemperatur    : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "therme/warmwassertemperatur/max", len, buf, 0, false);
			break;
		case 0x203:
//			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
//			//printf("ist Warmwassertemperatur    : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "therme/warmwassertemperatur/ist", len, buf, 0, false);
			break;
		case 0x204:
			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
			//printf("max Speichertemperatur      : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/speichertemperatur/max", len, buf, 0, false);
			break;
		case 0x205:
			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
			//printf("ist Speichertemperatur      : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/speichertemperatur/ist", len, buf, 0, false);
			break;
		case 0x206:
			len = snprintf(buf, max_len, "%02X", frame->data[0]);
			//printf("Störungsmeldung             : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/störungsmeldung", len, buf, 0, false);
			break;
		case 0x207:
			data = (int16_t)((frame->data[0] << 8) | frame->data[1]);
			len = snprintf(buf, max_len, "%.1f", (float)data / 100.0);
			//printf("Außentemperatur             : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/außentemperatur", len, buf, 0, false);
			break;
		case 0x209:
			len = snprintf(buf, max_len, "%d", frame->data[0]);
			//printf("Flamme                      : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/flamme", len, buf, 0, false);
			break;
		case 0x20a:
			len = snprintf(buf, max_len, "%d", frame->data[0]);
			//printf("Heizungspumpe               : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/pumpe", len, buf, 0, false);
			break;
		case 0x20b:
			len = snprintf(buf, max_len, "%d", frame->data[0]);
			//printf("Speicherladung              : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/speicherladung", len, buf, 0, false);
			break;
		case 0x20c:
			len = snprintf(buf, max_len, "%d", frame->data[0]);
			//printf("Winterbetrieb               : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "therme/winterbetrieb", len, buf, 0, false);
			break;
		case 0x20d:
//			len = snprintf(buf, max_len, "%d", frame->data[0]);
//			//printf("max Heizgeräteleistung      : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "therme/heizgeräteleistung", len, buf, 0, false);
			break;

		case 0x250:
			len = snprintf(buf, max_len, "%d", frame->data[0]);
			//printf("Heizbetrieb                 : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "regler/heizbetrieb", len, buf, 0, false);
			break;
		case 0x251:
//			len = snprintf(buf, max_len, "%d", frame->data[0]);
//			//printf("Heizleistung                : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "regler/heizleistung", len, buf, 0, false);
			break;
		case 0x252:
			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
			//printf("soll Vorlauftemperatur      : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "regler/vorlauftemperatur/soll", len, buf, 0, false);
			break;
		case 0x253:
//			len = snprintf(buf, max_len, "%d", frame->data[0]);
//			//printf("Sparbetrieb                 : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "regler/sparbetrieb", len, buf, 0, false);
			break;
		case 0x254:
//			len = snprintf(buf, max_len, "%d", frame->data[0]);
//			//printf("sollw. WW-Sofort            : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "regler/warmwasser-sofort", len, buf, 0, false);
			break;
		case 0x255:
			len = snprintf(buf, max_len, "%.1f", (float)frame->data[0] / 2.0);
			//printf("sollw. WW-Temperatur        : %s\r\n", buf);
			res = mosquitto_publish(mosq, NULL, "regler/speichertemperatur/soll", len, buf, 0, false);
			break;
		case 0x256:
			//printf("Uhrzeit                     : %d:%d Tag %d (%d)\r\n", frame->data[1], frame->data[2], frame->data[0], frame->data[3]);
			break;
		case 0x258:
//			len = snprintf(buf, max_len, "%d", frame->data[0]);
//			//printf("Witterungsgeführte regelung : %s\r\n", buf);
//			res = mosquitto_publish(mosq, NULL, "regler/witterungsgeführteregelung", len, buf, 0, false);
			break;

		default:
/*
			printf("                            Unknown 0x%03X [%d] ",frame->can_id, frame->can_dlc);

			for (i = 0; i < frame->can_dlc; i++)
				printf("%02X ",frame->data[i]);
			printf("\r\n");
*/
			break;
	}
	if(res != MOSQ_ERR_SUCCESS) {
		printf("Reconnect to broker\r\n");
		mosquitto_reconnect(mosq);
	}
}

int main(int argc, char **argv)
{
	int s, i, rc; 
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;
	struct mosquitto *mosq;

	printf("CAN Sockets Receive\r\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	mosquitto_lib_init();
	
	mosq = mosquitto_new("gastherme", true, NULL);

	rc = mosquitto_connect(mosq, "localhost", 1883, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	printf("We are now connected to the broker!\n");

	while(1) {
		nbytes = read(s, &frame, sizeof(struct can_frame));

	 	if (nbytes < 0) {
			perror("Read");
			return 1;
		}

		parse(&frame, mosq);
		usleep(100000);
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}

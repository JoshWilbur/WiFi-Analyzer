#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <linux/wireless.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "wifi_func.h"

int main(){
	setup(); // Run setup as defined in signal_strength.c
	struct iw_statistics wl_info;

	wl_info = wifi_stats(); // Obtain struct with wifi info
        int8_t rssi_dBm = (int8_t)wl_info.qual.level; // Cast struct value to 8 bit signed integer for a correct value
        printf("Signal level: %d dBm\n", rssi_dBm);

	close_socket(); // Close the UDP socket
	return 0;
}

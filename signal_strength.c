#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <linux/wireless.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

// TO DO:
// Change interface to a define? | Add link quality and other stats?

// Global variable declarations
int socket_fd;
struct iwreq wl_req;
struct iw_statistics wl_stats;
char *interface = "wlan0"; // Default Linux wireless name

// This function will set up the socket for obtaining stats
void setup(){
        // Allocate memory for structs
        memset(&wl_req, 0, sizeof(wl_req));
        memset(&wl_stats, 0, sizeof(wl_stats));

        // Open a UDP socket then error check
        socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_fd<0){
                fprintf(stderr,"Error opening socket: %s\n", strerror(errno));
                exit(1);
        }

        // Set up struct before requesting wireless data
        sprintf(wl_req.ifr_name, "%s", interface); // Input interface name
        wl_req.u.data.pointer = &wl_stats; // Place data into wl_stats struct when obtained
        wl_req.u.data.length = sizeof(wl_stats);
}

// This function will obtain signal strength in dBm
int signal_strength(){
	// Obtain wireless stats
        int result = ioctl(socket_fd, SIOCGIWSTATS, &wl_req);
        if (result == -1){
                fprintf(stderr,"Error socket stats: %s\n", strerror(errno));
                close(socket_fd);
                exit(1);
        }

        int strength_dBm = (int8_t)wl_stats.qual.level; // Cast struct value to 8 bit signed integer for a correct value
	return strength_dBm;
}

int main(){
	setup();
	int rssi = signal_strength();
	printf("Signal Level: %d dBm\n", rssi);
	close(socket_fd);
	return 0;
}

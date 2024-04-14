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

// Location of header file: /usr/include/linux/wireless.h

// Global variables
static int socket_fd;
static struct iwreq wl_req;
static struct iw_statistics wl_stats;
static char *interface = "wlan0"; // Default Linux wireless name

// This function will set up the socket and load in stats
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
}

// This function will output a struct containing wifi statistics
struct iw_statistics wifi_stats(){
        // Set up struct before requesting wireless data
        sprintf(wl_req.ifr_name, "%s", interface); // Input interface name
        wl_req.u.data.pointer = &wl_stats; // Place data into wl_stats struct when obtained
        wl_req.u.data.length = sizeof(wl_stats);

        // Obtain wireless stats
        int result = ioctl(socket_fd, SIOCGIWSTATS, &wl_req);
        if (result == -1){
                fprintf(stderr,"Error socket stats: %s\n", strerror(errno));
                close(socket_fd);
                exit(1);
        }
	return wl_stats;
}

// This function is self explainatory
void close_socket(){
	close(socket_fd);
}

int main(){
        setup(); // Run setup as defined in signal_strength.c
        struct iw_statistics wl_info;

        wl_info = wifi_stats(); // Obtain struct with wifi info
        int8_t rssi_dBm = (int8_t)wl_info.qual.level; // Cast struct value to 8 bit signed integer for a correct value
        printf("%d dBm", rssi_dBm);

        close_socket(); // Close the UDP socket
        return 0;
}

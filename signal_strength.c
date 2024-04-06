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
// Change interface to a define? | Move main code into a function when files linking together

int main(){
	int socket_fd, result;
	struct iwreq wl_req;
	struct iw_statistics wl_stats;
	char *interface = "wlan0"; // Default Linux wireless name

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

	// Obtain wireless statistics
        result = ioctl(socket_fd, SIOCGIWSTATS, &wl_req);
        if (result == -1){
                fprintf(stderr,"Error socket stats: %s\n", strerror(errno));
		close(socket_fd);
                exit(1);
        }

	// Print basic stats
	printf("Interface Name: %s\n", wl_req.ifr_name);
	printf("Link Quality: %d\n", wl_stats.qual.qual);
	printf("Signal Level: %d dBm\n", wl_stats.qual.level);

	close(socket_fd);
}

#include "network.h"
#include <fcntl.h>
int init_socket() {
    int sock = socket(PF_PACKET, SOCK_RAW, 0);
    int ret = 0;
    if(sock < 0) {
        ret = -1;
    }
    printf("aaaaaaaaa");
    return ret;
}
int release_socket(int fd) {
    int ret = 0;
    if(fd < 0) {
        ret = -1; 
        //return -1;
    }

    close(fd);
    return ret;
}
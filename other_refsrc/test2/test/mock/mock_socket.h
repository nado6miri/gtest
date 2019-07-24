#include <stdio.h>
 
int socket_internal = 1;
int close_internal = 0;
 
int fake_socket (int __domain, int __type, int __protocol) __THROW {
    printf("fake_sock...........");
    return socket_internal;
}
 
int fake_close(int fd) {
    return close_internal;
}
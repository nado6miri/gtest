#include "network.h"
int main(int argc, char** argv)
{
    int sock = init_socket();
    release_socket(sock);
    return 0;
}
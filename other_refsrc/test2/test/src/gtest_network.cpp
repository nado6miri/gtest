#include <gtest/gtest.h>
extern "C" {
#include "mock_socket.h"
#include "network.h"
}

extern int socket_internal;
extern int close_internal;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

 
TEST(GTestHelloworld, init_socket_normal) {
    socket_internal = 1;
    int sock = init_socket();
    //ASSERT_GT(sock, 0);
    ASSERT_EQ(sock, 0);
}


TEST(GTestHelloworld, init_socket_abnormal) {
     socket_internal = -1;
     int sock = init_socket();
     ASSERT_EQ(sock, -1);
}
 
TEST(GTestHelloworld, release_socket_normal) {
    int sock = 1;
    close_internal = 0;
    int ret = release_socket(sock);
    ASSERT_EQ(ret, 0);
}
 
// TEST(GTestHelloworld, release_socket_abnormal) {
//     int sock = -1;
//     int ret = release_socket(sock);
//     ASSERT_EQ(ret, -1);
// }
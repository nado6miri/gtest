#include "User.h"
#include <gtest/gtest.h>

//               ::testing::Test
//               |               |
//    TEST(UserTest, Test1)   UserTest       
//                               |
//                       TEST_F(UserTest, Test2)   



class UserTest : public ::testing::Test {

};

TEST_F(UserTest, Test2) {
	User user;
	printf("%d\n", user.age);
}

TEST(UserTest, Test1) {
	User user;
	printf("%d\n", user.age);
}

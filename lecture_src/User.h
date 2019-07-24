#ifndef USER_H
#define USER_H

// C++은 friend 문법이 있습니다.
//  : friend로 선언된 클래스가 클래스의 private 필드나 메소드에 접근할 수 있는 문법.

#include <gtest/gtest.h> // !!!

class User {
	int age;
public:
	User() : age(42) {}

	FRIEND_TEST(UserTest, Test1);  // !!!
	FRIEND_TEST(UserTest, Test2);  // !!!
};

#endif

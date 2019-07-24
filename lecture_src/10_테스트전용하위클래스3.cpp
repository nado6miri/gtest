#include <gtest/gtest.h>

#define class struct
#define private public
#include "User.h"

// C++ 에서는 위의 방법을 방어할 있는 설계 기법이 존재합니다.
//  : pImpl idioms(컴파일러 방화벽)
//    - Exceptional C++ Series
#if 0
// User.h
class UserImpl;  // !!
class User {
private:
	UserImpl* pImpl;
};

// User.cpp
class UserImpl {
public:
	int age;
};




#endif









// 로버트 C 마틴 - 클린 코드
//  : private 메소드는 public 메소드의 가독성을 높이기 위해서 사용해야 한다.
//  => 테스트 대상 메소드인 public 메소드를 검증하면서, 자연스럽게 private 메소드도 검증되어야 한다.

// 테스트 진영
//  : 검증되지 않은 private 메소드보다 검증된 public 메소드가 낫다.

TEST(UserTest, Test1) {
	User user;
	printf("%d\n", user.age);
}

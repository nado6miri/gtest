// 한계: 부모의 필드가 private 인 경우에는 사용할 수 없다.

// 10_테스트전용하위클래스2.cpp
class User {
public:
	User() : age(42) {}
protected:
	int age;
};

#include <gtest/gtest.h>

// SUT가 제공하는 필드나 메소드가 protected인 경우, 테스트 전용 하위 클래스를 통해서 접근하는 것이 가능하다.

class TestUser : public User {
// 부모의 age 필드의 접근 권한을 public으로 변경한다.
public:
	using User::age;
};

TEST(UserTest, Test1) {
	// User user;
	TestUser user;

	printf("%d\n", user.age);
}







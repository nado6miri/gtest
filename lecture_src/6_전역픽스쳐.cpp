// 전역 픽스쳐
// - Google Test에서 제공하는 기능.
// : 프로그램의 시작에서 초기화하고, 끝에서 정리하는 코드.
//
// 설치 방법 2가지
// 1) 전역 변수
// 2) main을 직접 작성

// 1) 전역 변수 - main을 작성하지 않을 경우.
#include <gtest/gtest.h> // Ctrl + w + f
#include <stdio.h>

TEST(SampleTestCase1, Test1) {}
TEST(SampleTestCase2, Test1) {}
TEST(SampleTestCase3, Test1) {}

class MyTestEnvironment : public ::testing::Environment {
public:
	virtual void SetUp() {
		printf("프로그램 시작에 관련된 초기화 코드\n");
	}

	virtual void TearDown() {
		printf("프로그램 종료시 정리 코드\n");
	}
};

#if 0
::testing::Environment* const test_env = 
	::testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	// 2. main을 직접 만들어서 등록하는 것이 좋다.
	::testing::AddGlobalTestEnvironment(new MyTestEnvironment);

	return RUN_ALL_TESTS();
}

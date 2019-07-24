// 1. include
#include <gtest/gtest.h>

// 1) 테스트 함수를 만드는 방법.
//  => TEST(테스트 케이스 이름, 테스트 이름)
TEST(TestCaseName, TestName) {
	// 테스트를 작성중이면, 실패하는 것이 좋다.

	// 테스트를 명시적으로 실패하고 싶을 때...
	// : 단언 함수
	//  => 단언문을 작성할 경우, 반드시 테스트 실패의 원인을 명시해야 합니다.
	FAIL() << "작성 중입니다."; 
}

// main을 직접 작성하는 것이 아니라, 이미 제공하는 main을 정적 라이브러이에 포함해서 사용하고 싶다.
// $ g++ ~/chansik.yun/gtest/googletest/src/gtest_main.cc -c -I.
// $ ar rcv libgtest.a gtest-all.o gtest_main.o
// r - gtest-all.o
// r - gtest_main.o
// $ g++ 1_시작.cpp -I. -lgtest -L. -pthread

#if 0
// 2. main
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif

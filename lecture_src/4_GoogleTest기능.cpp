#include <gtest/gtest.h>

// 1. 단언 매크로
//    ASSERT_EQ / NE / LT / GT / LE / GE ...
//    주의할 점
//     -> 단언문이 실패할 경우, 이후의 코드는 수행되지 않습니다.

// 테스트 함수 안에서는 하나의 테스트 단언문만 존재해야 한다.
//  => 너무 많은 테스트 함수가 만들어질 수 있다.

// 구글 테스트는 다른 형태의 단언 매크로를 제공하고 있습니다.
//  => EXPECT를 사용하면, 테스트가 실패하더라도, 이후의 코드를 수행합니다.
#if 0
TEST(GoogleTestSamle, Test1) {
	int expected1 = 1;
	int expected2 = 22;

	// Act
	// ASSERT_EQ(expected1, 11) << "Reason 1";  // !!
	// ASSERT_EQ(expected2, 22) << "Reason 2";
	EXPECT_EQ(expected1, 11) << "Reason 1";  // !!
	EXPECT_EQ(expected2, 22) << "Reason 2";
}
#endif

#include <string> // C++
                  // C: const char* / char[]

// 2. 문자열 비교 단언문
TEST(GoogleTestSample, Test2) {
	std::string s1 = "Hello";
	std::string s2 = "Hello";

	ASSERT_EQ(s1, s2);     // ==
	// EQ(==), NE(!=), LE(<=), GE(>=), LT(<), GT(>)
	//  : 사용자 정의 객체에 대해서 단언 매크로를 사용할 경우,
	//    위의 연산이 '연산자 오버로딩'을 통해 제공되어야만 합니다.

	const char* s3 = "Hello";
	const char* s4 = s2.c_str();

	// C의 문자열은 ASSERT_EQ / EXPECT_EQ를 통해 비교할 경우,
	// 제대로 동작하지 않을 수 있습니다.
	// ASSERT_EQ(s3, s4);
	ASSERT_STREQ(s3, s4);
}

// 3. 부동 소수점
TEST(GoogleTestSample, Test3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// ASSERT_DOUBLE_EQ(a, b);
	ASSERT_NEAR(a, b, 0.00000000001);

#if 0
	if (a == b) {
		printf("Same\n");
	} else {
		printf("Diff\n");
	}
#endif

	// ASSERT_EQ(a, b);
}

// 4. 예외 테스트
//  : 예외 처리 코드도 테스트에 포함시켜 검증해야 합니다.
void foo(const std::string& name) {
	if (name.empty()) {
		throw std::invalid_argument("name is empty");
	}
}

// 테스트의 시나리오
//  : foo함수에 빈 문자열을 전달하였을 때, invalid_argument 예외가 발생하는지 여부를 검증하고 싶다.
TEST(GoogleTestSample, Test4) {
	std::string empty_name = "";

	try {
		foo(empty_name);
		FAIL() << "기대한 예외가 발생하지 않았음..";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였음..";
	}
}

TEST(GoogleTestSample, Test4_Good) {
	std::string empty_name = "";

	ASSERT_THROW(foo(empty_name), std::invalid_argument);
	ASSERT_ANY_THROW(foo(empty_name)); // 어떤 예외든 상관없는 버전.
}

// 5. 테스트 비활성화
//  : 절대 비활성화하고자 하는 테스트를 주석처리 하면 안됩니다.
//  => 잊혀진다.
//   : 테스트 케이스의 이름 또는 테스트 함수의 이름이 DISABLED_로 시작하면 수행하지 않습니다.
// TEST(GoogleTestSamle, DISABLED_Test1) {

// xUnit Test Framework는 테스트를 비활성화하는 기능을 제공함과 동시에, 비활성화된 테스트를 별도로 동작시킬 수 있습니다.
// $ ./a.out --gtest_also_run_disabled_tests

TEST(DISABLED_GoogleTestSamle, Test1) {
	int expected1 = 1;
	int expected2 = 22;

	// Act
	// ASSERT_EQ(expected1, 11) << "Reason 1";  // !!
	// ASSERT_EQ(expected2, 22) << "Reason 2";
	EXPECT_EQ(expected1, 11) << "Reason 1";  // !!
	EXPECT_EQ(expected2, 22) << "Reason 2";
}






























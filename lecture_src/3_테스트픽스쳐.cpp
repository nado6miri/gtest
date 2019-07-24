#include <gtest/gtest.h>

class Calculator {
public:
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	
	double Display() { return 0; }
};

//------------------------------------
// 3_테스트픽스쳐
//
// Fixture
//  1. 정의: xUnit Test Pattern에서 SUT를 실행하기 위해 준비해야 하는
//           모든 것을 테스트 픽스쳐라고 합니다.
//  2. 픽스쳐를 구성하는 모든 로직 부분을 Fixture Setup이라고 합니다.

// Fixture를 설치하는 방법 3가지
// 1) Inline Setup
//  : 모든 픽스쳐 설치 코드를 테스트 함수 안에서 수행한다.
//  장점
//  - 픽스쳐 설치와 검증 로직에 대한 부분이 테스트 함수 안에 동시에 존재하기 때문에, 테스트 인과 관계 분석이 용이하다.
//  단점
//  - 모든 테스트 함수 안에서 픽스쳐 설치 코드가 중복된다.

// xUnit Test Pattern
//  TestSuite
//    TestCase1
//    TestCase2
//
// Google Test
//  TestCase
//     Test1
//     Test2


// ::testing::Test
//       |
//    CalculatorTest
//    |      |       |
//  TEST_F TEST_F  TEST_F

// 2) Delegation Setup
//  - 픽스쳐 설치에 대한 중복 코드를 별도의 함수로 묶는다.
// 1) 명시적인 테스트 케이스를 별도로 작성해야 합니다.
class CalculatorTest : public ::testing::Test {
// private:
protected:
    // TEST_F로 만든 자식 클래스의 테스트 함수 안에서 해당 기능에 접근하는 것이 가능합니다.
	Calculator* Create() { return new Calculator; }
	// Test Utility Method
	//   : 구글 테스트에서는 protected로 만들어야 합니다.
};

// 2) TEST_F 라는 매크로를 통해 테스트 함수를 작성해야 합니다.
TEST_F(CalculatorTest, Test1) {
	// Arrange
	Calculator* calc = Create();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);

	ASSERT_EQ(4, calc->Display()) << "2 + 2 == 4";
}

TEST_F(CalculatorTest, Display_2Plus2_Equals4) {
	// Arrange
	Calculator* calc = Create();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);

	// Assert
	ASSERT_EQ(4, calc->Display()) << "2 + 2 == 4";
}


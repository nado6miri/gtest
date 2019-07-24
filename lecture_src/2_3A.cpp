// 3A
//  : 테스트 함수를 구성하는 방법.
#include <gtest/gtest.h>


// SUT(System Under Test)
//  : 테스트 대상 코드
class Calculator {
public:
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	
	double Display() { return 0; }
};
//------------------------------------

// 3A
// 1. Arrange
//  : 객체를 생성하고, 필요한 경우에 적절하게 설정하고 준비한다.
// 2. Act
//  : 객체에 작용을 가한다.
// 3. Assert
//  : 기대하는 바를 단언한다.
              
// $  g++ 2_3A.cpp -I. -lgtest -L. -pthread
// Calculator -> CalculatorTest (TestCaseName) 
// 문제점 
// 1) 테스트 코드 안에서는 절대 제어 구문을 사용하면 안됩니다.
//    (조건문, 반복문, 예외 처리) 같은 구문을 사용하면 안됩니다.
//    => 단위 테스트는 유지보수의 비용이 작아야 합니다.
// 2) 현재 테스트의 이름으로는 테스트가 어떤 시나리오로 동작하는지 알 수
//    없다.
//    => 이름 규칙을 잘 정하는 것이 매우 중요합니다.
//    => ex) 테스트대상함수_테스트시나리오_기대값
TEST(CalculatorTest, Test1) {
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);

	// Assert
	// : 단위 테스트 프레임워크는 기대값과 실제값을 비교하는 다양한 함수를
	//   이미 제공하고 있습니다.
#if 0
	if (calc->Display() != 4) {
		FAIL() << "2 + 2 == 4";
	}
#endif
	// 인자의 순서에 신경써야 합니다.
	// ASSERT_EQ(expected, actual);
	// ASSERT_EQ(calc->Display(), 4) << "2 + 2 == 4";
	ASSERT_EQ(4, calc->Display()) << "2 + 2 == 4";
}

// TDD     => BDD
// Arrange -> Given
// Act     -> When
// Assert  -> Then

TEST(CalculatorTest, Display_2Plus2_Equals4) {
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);

	// Assert
	ASSERT_EQ(4, calc->Display()) << "2 + 2 == 4";
}

// 테스트 코드 품질
// 1) 가독성
// 2) 유지보수성
// 3) 신뢰성















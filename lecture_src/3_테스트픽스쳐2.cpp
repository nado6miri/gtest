#include <gtest/gtest.h>

class Calculator {
public:
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	
	double Display() { return 0; }
};
//-------
// 방법 3. Implicit Setup
//         : 암묵적 설치/해체
//  : xUnit Test Framework가 지원하는 기능입니다.
//  여러 테스트에서 같은 테스트 픽스쳐를 약속된 함수인 SetUp/TearDown에서 처리한다.

// 장점
//  : 테스트 코드의 중복을 제거하고, 불필요한 상호작용을 테스트 코드에서 분리할 수 있다.
// 단점
//  : 픽스쳐 설치가 테스트 코드 밖에 존재하므로, 테스트 코드만으로 테스트의 인과관계를 이해하기 어려울 수 있다.

// 자원 해지에 관련된 코드를 테스트 함수에 놓는 것은 위험하다.
// => 테스트가 실패할 경우, 테스트 코드의 나머지는 수행되지 않는다.
// => 테스트 프레임워크가 암묵적으로 호출하는 해체 함수를 이용하는 것이 안전한다.

// 4단계 테스트 패턴
//  : xUnit Test Pattern이 제안하는 테스트를 구성하는 방법
//  1단계 - 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 설정하는 작업.
//  2단계 - SUT와 상호작용한다.
//  3단계 - 기대 결과를 확인한다.
//  4단계 - 테스트 픽스쳐를 해체해서, 테스트 시작 전으로 돌려놓는다.

//  xUnit Test Framework은 각각의 테스트가 독립적일수 있도록,
//  제공하는 기능이 있습니다.


class CalculatorTest : public ::testing::Test {
protected:
	Calculator* Create() { return new Calculator; }

	Calculator* calc;
	virtual void SetUp() override {
		printf("SetUp()\n");
		calc = Create();
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
		delete calc;
	}
};

TEST_F(CalculatorTest, Test1) {
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);

	ASSERT_EQ(4, calc->Display()) << "2 + 2 == 4";

	printf("End\n");
}

TEST_F(CalculatorTest, Display_2Plus2_Equals4) {
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);

	// Assert
	ASSERT_EQ(4, calc->Display()) << "2 + 2 == 4";

	printf("End\n");
}


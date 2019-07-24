// 9_파라미터화 테스트
//  : 입력 데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심의 테스트 코드의 중복을 없애주는 기법.
//  => xUnit Test Framework가 지원하는 기능입니다.

// 문제점
// 1) 데이터의 수가 적다면, 적용하지 않는 것이 좋을 수도 있다.
//    -> 코드의 복잡도가 올라간다.
// 2) 테스트의 이름에서 어떤 데이터를 검증하는지 알수없다.
//    -> jUnit은 이름을 변경할 수 있는 기능을 제공합니다.
// 3) 런타임에 데이터를 로드하며 수행하는 것이 힘들다.
//    -> jUnit에서 해당 기능을 제공합니다.

bool IsPrime(int value) {
	for (int i = 2; i < value ; ++i) {
		if (value % i == 0)
			return false;
	}
	return true;
}

#include <gtest/gtest.h>

// int data[] = { 11, 13, 17, 23, 41 };

// 1. 파라미터화 테스트를 위한 테스트 케이스 클래스를 만들어야 합니다.
// class ParamTest : public ::testing::Test {};
class ParamTest : public ::testing::TestWithParam<int> {
protected:
	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

// 2. Data Set 정의해야 합니다.
int data[] = { 11, 13, 17, 23, 42 };
INSTANTIATE_TEST_CASE_P(primeValues, ParamTest, ::testing::ValuesIn(data)); 

// 3. 이제는 해당 데이터를 이용하는 다양한 테스트를 만들면 됩니다.
// TEST / TEST_F / TEST_P
TEST_P(ParamTest, isPrime) {
	int input = GetParam();  // 값을 얻어오는 함수입니다.

	EXPECT_TRUE(IsPrime(input));
}

TEST_P(ParamTest, isPrime2) {
	int input = GetParam();  // 값을 얻어오는 함수입니다.

	EXPECT_TRUE(IsPrime(input));
}






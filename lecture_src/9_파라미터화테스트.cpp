// 9_파라미터화 테스트
//  : 입력 데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심의 테스트 코드의 중복을 없애주는 기법.
//  => xUnit Test Framework가 지원하는 기능입니다.

bool IsPrime(int value) {
	for (int i = 2; i < value ; ++i) {
		if (value % i == 0)
			return false;
	}
	return true;
}

#include <gtest/gtest.h>

// 파라미터화 테스트가 없다면
// int data[] = { 11, 13, 17, 23, 41 };
TEST(ParamTest, PrimeTest) {
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(17));
	EXPECT_TRUE(IsPrime(23));
	EXPECT_TRUE(IsPrime(42));
}

TEST(ParamTest, PrimeTest2) {
	int data[] = { 11, 13, 17, 23, 42 };
	for (int i = 0; i < 5; ++i)
		EXPECT_TRUE(IsPrime(data[i]));
}

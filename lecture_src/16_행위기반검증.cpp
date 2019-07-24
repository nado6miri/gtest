#include <gmock/gmock.h>

struct User {
	virtual ~User() {}

	virtual void Stop() = 0;
	virtual void Move(int x, int y) = 0;

	virtual std::string GetTime() = 0;
};

// mock_gen.py
class MockUser : public User {
public:
	MOCK_METHOD0(Stop, void());
	MOCK_METHOD2(Move, void(int, int));

	MOCK_METHOD0(GetTime, std::string());
};

// 행위 기반 검증
// 1) 호출 여부 검증 - EXPECT_CALL
// 2) 호출 횟수 검증 - Times(N) / ::testing::AnyNumber
// 3) 호출 순서 검증 - ::testing::InSequence
// 4) 인자 검증

// 5) 결과 제어 기능
// ON_CALL
// ::testing::Return
#include <iostream>

using ::testing::Return;
TEST(MockTest, Stub) {
	MockUser stub;
	ON_CALL(stub, GetTime()).WillByDefault(Return("17:00"));

	std::cout << stub.GetTime() << std::endl;
}


void foo(User* p) {
	p->Move(10, 32);
	p->Stop();
}

using ::testing::_;
using ::testing::AnyNumber;
// Google Mock은 mock 객체가 파괴되는 시점에 검증을 수행합니다.
TEST(MockTest, Test1) {
	// 순서 검증이 필요하다면 아래 한줄만 추가하면 됩니다.
	::testing::InSequence seq; 

	MockUser mock;
	// MockUser* mock = new MockUser;

	// EXPECT_CALL(mock, Stop()).Times(3);
	// EXPECT_CALL(mock, Stop()).Times(AnyNumber());
	EXPECT_CALL(mock, Move(10, _));
	EXPECT_CALL(mock, Stop());
	// EXPECT_CALL(mock, Move(10, 32));
	

	foo(&mock);
	// delete mock;
}








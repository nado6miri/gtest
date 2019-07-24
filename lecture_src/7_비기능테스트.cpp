// 7_비기능테스트
#include <gtest/gtest.h>

#include <unistd.h>  // sleep

// 비기능 테스트: 기능의 시간, 메모리 누수..
// g++ 7_비기능테스트.cpp -I. -lgtest -L. -pthread
void foo() {
	sleep(3);   // 3 sec
}

class TimeTest : public ::testing::Test {
protected:
	time_t startTime;
	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < 2) << "시간 초과: " << duration << " 초 걸렸습니다.";
	}
};

// 2초 안에서 해당 동작이 수행되어야 한다.
TEST_F(TimeTest, fooTest) {
	foo();
}





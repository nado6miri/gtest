// 7_비기능테스트
#include <gtest/gtest.h>

#include <unistd.h>  // sleep

void foo() {
	sleep(3);   // 3 sec
}

class TimeTest : public ::testing::Test {
protected:
	time_t pivot;
	time_t startTime;

	virtual void SetUp() override {
		startTime = time(0);
		pivot = 0;
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		if (pivot != 0) {
			EXPECT_TRUE(duration < pivot) << "시간 초과: " << duration << " 초 걸렸습니다.";
		}
	}
};

TEST_F(TimeTest, fooTest) {
	pivot = 1; // 1초 안에서 수행되어야 합니다.

	foo();
}

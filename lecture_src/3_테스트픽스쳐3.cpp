
#include <gtest/gtest.h>

// xUnit Test Framework가 테스트를 수행하는 방법.
//  => 신선한 픽스쳐의 전략
// Test Runner
//  MyTest testcase = new MyTest;
//  testcase->SetUp();
//  testcase->Test1();
//  testcase->TearDown();
//
//  MyTest testcase = new MyTest;
//  testcase->SetUp();
//  testcase->Test2();
//  testcase->TearDown();


class MyTest : public ::testing::Test {
protected:
	MyTest() { printf("MyTest\n"); }

	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

TEST_F(MyTest, Test1) {
	printf("  Test1\n");
}

TEST_F(MyTest, Test2) {
	printf("  Test2\n");
}












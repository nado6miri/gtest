#include <iostream>
using namespace std;

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Google Test
//  => 테스트의 결과를 원하는 형태로 변경하는 것이 가능합니다.
class MyPrinter : public ::testing::EmptyTestEventListener {
	virtual void OnTestStart(const ::testing::TestInfo& info) {
		cout << "*****************************************" << endl;
		cout << "name: " << info.name() << endl;
		cout << "test_case_name: " << info.test_case_name() << endl;
	}
	virtual void OnTestPartResult(const ::testing::TestPartResult& result) {
		bool fail = result.failed();
		cout << (fail ? "실패" : "성공") << endl;
	}
	virtual void OnTestEnd(const ::testing::TestInfo& info) {
		cout << "*****************************************" << endl;
	}
};


// SampleTest.foo
TEST(SampleTest, foo) {
	RecordProperty("cpu", "1.2");	
}

// SampleTest.goo
TEST(SampleTest, goo) {
	RecordProperty("cpu", "1.5");	
}
	
// SampleTest.*
// *.foo


int main(int argc, char **argv) {
	::testing::InitGoogleMock(&argc, argv);

	// 1. 리스너의 목록을 얻어 옵니다.
	::testing::TestEventListeners& listeners 
		= ::testing::UnitTest::GetInstance()->listeners();
	// 2. 등록합니다.
	listeners.Append(new MyPrinter);

	return RUN_ALL_TESTS();
}







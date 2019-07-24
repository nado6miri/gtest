
// Mock Object
#include <stdio.h>
#include <string>
#include <vector>

// 분산 로거
//  : 전달된 로깅 메시지를 등록된 타겟에게 전파하는 역활
enum DLogLevel {
	INFO, WARN, ERROR,
};

struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual ~DLogTarget() {}
};

class DLog {
	std::vector<DLogTarget*> targets;
public:
	void AddTarget(DLogTarget* p) { targets.push_back(p); }
	
	void Write(DLogLevel level, const std::string& message) {
		for (DLogTarget* e : targets) {
			// e->Write(level, message);
		}
	}
};

//-----------------------------------------------
#include <gtest/gtest.h>
#include <algorithm> // find

// SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서, 테스트 안된 요구 사항이 있다.
// 1) 테스트 스파이 패턴
//   : 목격한 일을 기록해두었다가, 나중에 테스트에서 사용할 수 있도록 만들어진 테스트 대역
// 2)  모의 객체
//   : 행위 기반 검증으로 해결하자.
//    -> 메소드의 호출 여부, 호출 횟수, 호출 순서를 통해 행위 기반 검증을 수행하면 된다.
//    => 모의 객체
//    => Mock Framework
//      Java: jMock, EasyMock, [Mockito -> Spock]
//      C++:  Google Mock

// 1. include
#include <gmock/gmock.h>

// 2. Google Mock을 사용하기 위해서 작성해야 하는 코드 작업
// => googlemock/scripts/generator/gmock_gen.py 을 이용하면 자동으로 생성할 수 있습니다.
class DLogTargetMock : public DLogTarget {
public:
	// void Write(DLogLevel level, const std::string& message)
	// MOCK_METHOD{인자의 개수}(함수의 이름, 함수의 타입)
	
	MOCK_METHOD2(Write, void (DLogLevel level, const std::string& message));
};

class DLogTest : public ::testing::Test {
};

TEST_F(DLogTest, WriteTest) {
	DLog log;
	DLogTargetMock mock1, mock2;
	DLogLevel level = INFO;
	std::string message = "test_info_message";
	log.AddTarget(&mock1);
	log.AddTarget(&mock2);

	// Assert - 행위 기반 검증 시나리오
	EXPECT_CALL(mock1, Write(level, message));
	EXPECT_CALL(mock2, Write(level, message));

	// Act
	log.Write(level, message);
}

// 호출 여부
// 호출 횟수
// 호출 순서
//     +
//    Stub


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
			e->Write(level, message);
		}
	}
};

//-----------------------------------------------
#include <gtest/gtest.h>
#include <algorithm> // find

// SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서, 테스트 안된 요구 사항이 있다.
// => 테스트 스파이 패턴
//   : 목격한 일을 기록해두었다가, 나중에 테스트에서 사용할 수 있도록 만들어진 테스트 대역
class SpyTarget : public DLogTarget {
	std::vector<std::string> logs;

	std::string concat(DLogLevel level, const std::string& message) {
		static const char* level_string[] = {
			"INFO", "WARN", "ERROR",
		};
		return std::string(level_string[level]) + "@" + message;
	}

public:
	void Write(DLogLevel level, const std::string& message) {
		logs.push_back(concat(level, message));
	}

	bool IsReceived(DLogLevel level, const std::string& message) {
		return std::find(logs.begin(), logs.end(), 
				concat(level, message)) != logs.end();
	}
};

class DLogTest : public ::testing::Test {
};

TEST_F(DLogTest, WriteTest) {
	DLog log;
	SpyTarget spy1, spy2;
	DLogLevel level = INFO;
	std::string message = "test_info_message";
	log.AddTarget(&spy1);
	log.AddTarget(&spy2);

	log.Write(level, message);

	EXPECT_TRUE(spy1.IsReceived(level, message));
	EXPECT_TRUE(spy2.IsReceived(level, message));
}

// 테스트 대역
//  : 테스트 대상 코드를 격리한다.
//  -> 단위 테스트의 성공/실패가 SUT에 의해 결정되도록 통제한다.
//
// 테스트 대역 종류 - xUnit Test Pattern
//  1) Test Stub Pattern   -> Stub
//  2) Fake Object Pattern -> Fake
//  3) Test Spy Pattern    -> Spy
//  4) Mock Object Pattern -> Mock

// 테스트 대역
//   : 무조건 적용할 수 없습니다.
//     SUT가 테스트 대역을 적용할 수 있는 형태로 설계되어 있어야 합니다.
//   BDD(행위 주도 개발)
//-----------------------------------------------------------------
#include <string>

class FileSystem {
public:
	bool IsValid(const std::string& filename) { return false; }
};

class Logger {
public:
	// 확장자를 제외한 파일 이름이 5글자 이상이어야 한다.
	// hello.log  -> hello(다섯 글자 이상)
	bool IsValidFilename(const std::string& filename) {
		// 1. 파일 이름이 다섯글자 인지 체크
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		// 2. 파일 시스템에서 생성 가능한 파일인지 체크.
		FileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

//-----------------------------------------------------------
#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test {
protected:
};

TEST_F(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string filename = "bad.log";

	ASSERT_FALSE(logger.IsValidFilename(filename)) 
		<< "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, IsValidFilename_NameLongerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string filename = "valid_name.log";
	
	bool actual = logger.IsValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}

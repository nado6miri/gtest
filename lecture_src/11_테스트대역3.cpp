#include <string>

// C++의 인터페이스
struct IFileSystem {
	virtual bool IsValid(const std::string& filename) = 0; // 순수 가상 함수
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) { return false; }
};

class Logger {
private:
	IFileSystem* fs;
public:
	Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}
	

	bool IsValidFilename(const std::string& filename) {
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5)
			return false;

		// FileSystem* fs = new FileSystem;
		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

//-----------------------------------------------------------
#include <gtest/gtest.h>

class StubFileSystem : public IFileSystem {
public:
	virtual bool IsValid(const std::string& filename) {
		return true;
	}
};


class LoggerTest : public ::testing::Test {
protected:
};

TEST_F(LoggerTest, IsValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string filename = "bad.log";

	ASSERT_FALSE(logger.IsValidFilename(filename)) 
		<< "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, IsValidFilename_NameLongerThan5Chars_ReturnsTrue) {
	StubFileSystem stub;
	Logger logger(&stub);
	std::string filename = "valid_name.log";
	
	bool actual = logger.IsValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}






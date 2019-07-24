#include <string>

// 테스트 대역을 적용하기 위해서는, 의존 객체와 느슨한 결합이 되어야 합니다.
//  : 아래 코드는 강한 결합입니다.
//  강한 결합
//    : 의존 객체를 사용할 때, 구체적인 타입에 의존하는 설계
//  약한 결합
//    1) 의존 객체를 직접 참조하는 것이 아니라, 인터페이스나 추상 타입에 의존해야 한다.
//    => DIP(의존 관계 역전 원칙)
//    2) 인터페이스 타입을 통해 객체의 동작을 수행해야 한다.
//    3) 의존 객체를 직접 생성하면 안됩니다. 
//       new라는 연산은 강한 결합을 생성합니다.
//       외부에서 생성된 객체를 전달받아야 합니다.
//        => DI(의존성 주입 설계)
//        의존성 주입 방법 2가지
//        - 생성자 주입
//          : 의존 객체가 필수적일 때
//        - 메소드 주입
//          : 의존 객체가 선택적일 때

// C++의 인터페이스
struct IFileSystem {
	virtual bool IsValid(const std::string& filename) = 0; // 순수 가상 함수
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) { return false; }
};

// 틈새 만들기
//  : 테스트 대역을 적용할 수 있는 형태로 변경하는 작업
//   => 기존에 사용하던 인터페이스와 차이가 없어야 한다.

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
	// 의존성 주입을 사용할 때, 의존 객체를 직접 생성해서 주입하는 방식
	//  => 빈자의 의존성 주입.
	//   : 의존성 주입 프레임워크
	//    Java: Dagger2
	//    C++: Boost DI
	Logger logger;
	std::string filename = "valid_name.log";
	
	bool actual = logger.IsValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}








#include <string>

class User {
private:
	std::string name;
	int age;

public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string getName() const {
		return name;
	}

	int getAge() const {
		return age;
	}
};

struct IDatabase {
	virtual void Save(const std::string& name, int age) = 0;
	virtual User* Load(const std::string& name) = 0;

	virtual ~IDatabase() {}
};

// User 객체를 데이터베이스 저장하고, 불러오는 역활.
class UserManager {
private:
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* p) {
		database->Save(p->getName(), p->getAge());
	}

	User* Load(const std::string& name) {
		return database->Load(name);
	}
};

#include <map>
#include <gtest/gtest.h>

// 13_Fake Object
// 1) 의존하는 협력객체가 아직 준비되지 않아서, SUT를 검증할 수 없다.
// 2) 의존하는 협력객체를 사용하기 어려워서, SUT를 검증할 수 없다.

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void Save(const std::string& name, int age) {
		User* user = new User(name, age);
		data[name] = user;
	}

	User* Load(const std::string& name) {
		return data[name];
	}
};

class UserManagerTest : public ::testing::Test {
};

// 연산자 재정의 함수!!
bool operator==(const User& lhs, const User& rhs) {
	return lhs.getName() == rhs.getName() &&
		lhs.getAge() == rhs.getAge();
}

TEST_F(UserManagerTest, LoadTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string name = "test_name";
	int age = 42;
	User user(name, age);

	manager.Save(&user);
	User* actual = manager.Load(name);

	// 사용자 정의 객체에 대해서, ASSERT_EQ/NE... 사용하기 위해서는
	// 연산자 재정의 함수가 필요합니다.
	ASSERT_EQ(user, *actual);
}

// Docker
//  A -> python 2
//  B -> python 3
//  C -> Node 6
//  D -> Node 8
//
//  [A + Env] : Image -> Container











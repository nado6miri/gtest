#include <string>

// 스위트 픽스쳐
// : 신선한 픽스쳐의 전략이 아닌, 공유 픽스쳐의 전략을 사용하도록 변경된다. 
// 이전의 테스트가 픽스쳐를 망가뜨릴 경우, 이후의 테스트의 결과의 신뢰성이 깨질 수 있다.
// => 이제는 각각의 테스트는 더 이상 독립적이지 않습니다.
// : 공유 픽스쳐 전략에서 변덕스러운 테스트가 발생한다면, 테스트 케이스를 분리해서 문제를 찾을 수 있다.

#include <unistd.h>

class Database {
public:
	void Connect() { sleep(1); }
	void Disconnect() { sleep(2); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return false; }
};

//--------------------------------------
#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
	static std::string test_id;
	static std::string test_password;

	static Database* database;
	virtual void SetUp() override {
	}

	virtual void TearDown() override {
	}

	// Suite Fixture Setup / Teardown
	static void SetUpTestCase() {
		printf("SetUpTestCase\n");
		database = new Database;
		database->Connect();
	}

	static void TearDownTestCase() {
		printf("TearDownTestCase\n");
		database->Disconnect();
		delete database;
	}
};

std::string DatabaseTest::test_id = "test_id";
std::string DatabaseTest::test_password = "test_password";
Database* DatabaseTest::database = nullptr;

TEST_F(DatabaseTest, LoginTest) {
	database->Login(test_id, test_password);

	ASSERT_TRUE(database->IsLogin());
}

TEST_F(DatabaseTest, LogoutTest) {
	database->Login(test_id, test_password);
	database->Logout();

	ASSERT_FALSE(database->IsLogin());
}

TEST_F(DatabaseTest, Test1) {}

#if 0
TEST_F(DatabaseTest, LoginTest) {
	Database* database = new Database;
	database->Connect();
	std::string test_id = "test_id";
	std::string test_password = "test_password";

	database->Login(test_id, test_password);

	ASSERT_TRUE(database->IsLogin());

	database->Disconnect();
	delete database;
}

TEST_F(DatabaseTest, LogoutTest) {
	Database* database = new Database;
	database->Connect();
	std::string test_id = "test_id";
	std::string test_password = "test_password";

	database->Login(test_id, test_password);
	database->Logout();

	ASSERT_FALSE(database->IsLogin());

	database->Disconnect();
	delete database;
}
#endif














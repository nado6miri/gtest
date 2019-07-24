#include <string>

// 스위트 픽스쳐

#include <unistd.h>

// 가정
//  : Connect / Disconnect의 동작이 느리다.
// => 픽스쳐를 설치하고 해체하는 작업이 느린경우...
// => 테스트 함수를 추가할 때마다 전체적인 테스트가 느려지는 문제가 발생합니다.

// Slow Test 문제
//  : 테스트가 너무 느려서, 개발자들이 SUT가 변경되어도 매번 테스트를 수행하지 않는다.
//  : 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.

// Global Fixture SetUp

// DatabaseTest::SetUp() - Suite Fixture Setup
// DatabaseTest testcase = new DatabaseTest;
// testcase->SetUp()
// testcase->LoginTest();
// testcase->TearDown();

// DatabaseTest testcase = new DatabaseTest;
// testcase->SetUp()
// testcase->LogoutTest();
// testcase->TearDown();
// DatabaseTest::TearDown(); - Suite Fixture Teardown
//
// Global Fixture TearDown

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

	Database* database;
	virtual void SetUp() override {
		database = new Database;
		database->Connect();
	}

	virtual void TearDown() override {
		database->Disconnect();
		delete database;
	}

	// Suite Fixture Setup / Teardown
	static void SetUpTestCase() {
		printf("SetUpTestCase\n");
	}

	static void TearDownTestCase() {
		printf("TearDownTestCase\n");
	}
};

std::string DatabaseTest::test_id = "test_id";
std::string DatabaseTest::test_password = "test_password";

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














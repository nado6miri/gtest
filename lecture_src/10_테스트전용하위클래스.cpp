#include <stdio.h>
// 10_테스트전용하위클래스 패턴
// SUT
class Engine {
public:
	virtual void Start() { printf("Engine Start...\n"); }
	virtual ~Engine() {}
};
// 부모의 동작(메소드)을 하위 클래스를 통해 변경하기 위해서는 반드시,
// 부모의 인터페이스가 virtual 함수이어야 한다.

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	virtual void Go() {
		// ...
		engine->Start();
	}
};
//--------------------------------------------
#include <gtest/gtest.h>
// 자동차 Go가 호출되었을 때, engine에 대해서 Start가 제대로 호출되었는지 여부를 검증하고 싶다.

// 제품 코드를 변경하지 않고, 테스트에 필요한 기능만 추가하는 하위 클래스.

#if 0
class CarTest : public ::testing::Test {};

TEST_F(CarTest, engineTest) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// assert
}
#endif

class TestEngine : public Engine {
public:
	bool isStarted;
	TestEngine() : isStarted(false) {}

	virtual void Start() override {
		Engine::Start();
		isStarted = true;  // !!!
	}
};

class CarTest : public ::testing::Test {};

TEST_F(CarTest, engineTest) {
	// Engine engine;
	TestEngine engine;
	Car car(&engine);

	car.Go();
	
	EXPECT_TRUE(engine.isStarted);
}

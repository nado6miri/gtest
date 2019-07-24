#include <gtest/gtest.h>

// 특정 객체에 대해서 동작 수행 후 메모리가 제대로 해지되었는지 여부를
// 검증할 수 있다.
// -> C++은 클래스의 메모리 할당 연산을 재정의하는 것이 가능합니다.
//  : tcmalloc, jemalloc
class Image {
#ifdef LEAK_TEST
public:
	static int allocCount;

	void* operator new(size_t size) {
		printf("객체 할당\n");
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("객체 해지\n");
		--allocCount;
		free(p);
	}
#endif
};

#ifdef LEAK_TEST
int Image::allocCount = 0;
#endif

class ImageTest : public ::testing::Test {
protected:
	int allocCount;
	virtual void SetUp() override {
#ifdef LEAK_TEST
		allocCount = Image::allocCount;
#endif
	}

	virtual void TearDown() override {
#ifdef LEAK_TEST
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(0, diff) << diff << " Objects leaked";
#endif
	}
};

void foo() {
	Image* img1 = new Image;
	Image* img2 = new Image;
	Image* img3 = new Image;

	printf(".....\n");
	delete img1;
}

TEST_F(ImageTest, imageTest) {
	foo();
}

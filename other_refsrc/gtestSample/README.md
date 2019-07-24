Googletest Samples
=======

### 본 page는 개인적인 코드 분석을 바탕으로 googletest sample의 내용을 정리한 page입니다.

원본 sample : https://github.com/google/googletest/tree/master/googletest/samples

```shell
# 각 예제 빌드 방법
make sample1 ... make sample10
```
<br/>


예제 설명 
=======



##   Sample #1 shows the basic steps of using googletest to test C++ functions.
##   Sample #2 shows a more complex unit test for a class with multiple member
##   Sample #3 uses a test fixture.

*테스트 픽스쳐는 다중 테스트를 위해 동일한 데이터 구성 및 해제가 필요할 때 사용함.*

```cpp
class Template : class FixtureTest : public ::testing::Test
virtual void SetUp()   // 각 TEST에 선행하여 각각 수행
virtual void TearDown() // 각 TEST 완료 직후 각각 수행
TEST_F(FixtureTest, test1)  // TEST대신 TEST_F를 사용해야 함.
```
##   Sample #4 teaches you how to use googletest and `googletest.h` together to get the best of both libraries.
*I couldn't understand sample4. It's just simple sample code.*
##   Sample #5 puts shared testing logic in a base test fixture, and reuses it in derived fixtures.
*SetUp 과 TearDown을 이용하여 unit test 수행시간 측정*

##   Sample #6 demonstrates type-parameterized tests.
*같은 TC를 여러 종류의 TYPE에 대해 Test를 수행*

```cpp
template <class T>, template <>
class PrimeTableTest : public testing::Test {

//1. 모든 TYPE을 알고 있는 경우
typedef Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable> Implementations;
TYPED_TEST_CASE(PrimeTableTest, Implementation);
TYPED_TEST(PrimeTableTest, ReturnsFalseForNonPrimes) {

//2. 모든 TYPE을 알지 못하는 경우
TYPE_TEST_CASE_P(PrimeTableTest2)
TYPED_TEST_P(PrimeTableTest2, ReturnsFalseForNonPrimes) {
REGISTER_TYPED_TEST_CASE_P (
    PrimeTableTest2,
    CanGetNextPrime, ReturnsFalseForNonPrimes, ReturnsTrueForPrimes );
typedef Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable>
    PrimeTableImplementations;
// instance를 만들지 않으면 수행되지 않음.    
INSTANTIATE_TYPED_TEST_CASE_P(OnTheFlyAndPreCalculated,    // Instance name
                              PrimeTableTest2,             // Test case name
                              PrimeTableImplementations);  // Type lis
```

##   Sample #7 teaches the basics of value-parameterized tests.
*GetParm 함수 포인터를 이용하여 여러가지의 함수들을 param으로 받아온다.*
```cpp
class PrimeTableTestSmpl7 : public TestWithParam<CreatePrimeTableFunc*> {
  virtual void SetUp() { 
    printf("SetUp\n");
    table_ = (*GetParam())(); }    

// instance를 만들지 않으면 수행되지 않음.  
INSTANTIATE_TEST_CASE_P(OnTheFlyAndPreCalculated,  // instance name
                        PrimeTableTestSmpl7,    // name of Test Suite
                        Values(&CreateOnTheFlyPrimeTable,   // return of GetParam()
                               &CreatePreCalculatedPrimeTable<1000>));

```

##   Sample #8 shows using `Combine()` in value-parameterized tests.
*combine 기능을 통해 N x N개의 test를 수행*
```cpp
class PrimeTableTest : public TestWithParam< ::testing::tuple<bool, int> > {
force_on_the_fly = ::testing::get<0>(GetParam());   // first value
max_precalculated = ::testing::get<1>(GetParam());   // second value
INSTANTIATE_TEST_CASE_P(MeaningfulTestParameters,
                        PrimeTableTest,
                        Combine(Bool(), Values(1, 10)));
```

##   Sample #9 shows use of the listener API to modify Google Test's console output and the use of its reflection API to inspect test results.
*Customized 된 출력을 하는 방법 (listener를 변경하여~)*

```cpp
//1. class 만들기
class TersePrinter : public EmptyTestEventListener

//2. 관련된 member 함수 define
virtual void OnTestProgramStart(const UnitTest& /* unit_test */) {}
virtual void OnTestProgramEnd(const UnitTest& unit_test)
virtual void OnTestStart(const TestInfo& test_info)
virtual void OnTestPartResult(const TestPartResult& test_part_result)
virtual void OnTestEnd(const TestInfo& test_info)

//3. main에서 default Listener를 삭제하고 Custom Listener를 등록
UnitTest& unit_test = *UnitTest::GetInstance();
TestEventListeners& listeners = unit_test.listeners();
delete listeners.Release(listeners.default_result_printer()); // 기존 삭제
list
```

##   Sample #10 shows use of the listener API to implement a primitive memory leak checker.
*9번의 listener API를 이용하여 메모리 leakage를 측정하는 예제*
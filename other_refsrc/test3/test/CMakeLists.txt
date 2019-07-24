####################
## common setting
####################
#enable_testing()
#find_package(GTest REQUIRED)

# test file의 이름을 지정한다.
set(GTEST_EXE "gtest_mock")

# gtest path를 설정한다.
set(GTEST_PATH ~/sdetshare/workspace/gtest/googletest)
include_directories(${GTEST_PATH}/googletest/include ${GTEST_PATH}/googlemock/include) # google test 관련 include경로 지정
link_directories(${GTEST_PATH}/googletest/build)
link_directories(${GTEST_PATH}/googlemock/build)

include_directories(${CMAKE_SOURCE_DIR}/src)

# libgtest.a libgmock.a libpthread.a 를 포함시킨다.
set(TEST_LIBRARIES
  gtest
  gmock
  pthread
)
 
######################
# build setting - coverage option을 추가한다.
######################
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${FAKE_DEFINE} -coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -isystem -coverage ")
 
######################
# Unit Test setting
######################
set(UNIT_TEST_SRC_LIST
  ${CMAKE_SOURCE_DIR}/test/src/gtest_mock.cpp
)
 
add_executable(${GTEST_EXE} ${UNIT_TEST_SRC_LIST})
target_link_libraries(${GTEST_EXE} ${TEST_LIBRARIES})
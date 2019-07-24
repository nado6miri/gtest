####################
## common setting
####################
#enable_testing()
#find_package(GTest REQUIRED)

# test file의 이름을 지정한다.
set(GTEST_EXE "gtest_fake")

# gtest path를 설정한다.
set(GTEST_PATH ~/sdetshare/workspace/gtest/googletest)
include_directories(${GTEST_PATH}/googletest/include ${GTEST_PATH}/googlemock/include) # google test 관련 include경로 지정
include_directories(./mock) # test file에 대한 include경로 지정

link_directories(${GTEST_PATH}/googletest/build)
link_directories(${GTEST_PATH}/googlemock/build)

set(TEST_LIBRARIES
  gtest
  pthread
)
 
######################
# build setting - coverage option을 추가한다. 그리고 -D를 이용해서 fake 함수를 지정한다. (hooking)
######################
set(FAKE_DEFINE "-Dsocket=fake_socket")
set(FAKE_DEFINE "${FAKE_DEFINE} -Dclose=fake_close")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${FAKE_DEFINE} -coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -isystem .  -coverage ")


######################
# Unit Test setting
######################
set(UNIT_TEST_SRC_LIST
  ${CMAKE_SOURCE_DIR}/src/network.c
  ${CMAKE_SOURCE_DIR}/test/src/gtest_network.cpp
)
 
# unit test 실행 target 을 만들때 지정된 source files를 이용해서 실행파일을 생성.
add_executable(${GTEST_EXE} ${UNIT_TEST_SRC_LIST})

# link library는 libgtest.a libpthread.a를 link한다.
target_link_libraries(${GTEST_EXE} ${TEST_LIBRARIES})
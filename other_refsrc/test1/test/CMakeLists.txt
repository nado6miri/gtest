####################
## common setting
####################
#enable_testing()
#find_package(GTest REQUIRED)

# test file의 이름을 지정한다.
set(GTEST_EXE "gtest_sum")

# gtest path를 설정한다.
set(GTEST_PATH ~/sdetshare/workspace/gtest/googletest)
include_directories(${GTEST_PATH}/googletest/include ${GTEST_PATH}/googlemock/include) # google test 관련 include경로 지정
link_directories(${GTEST_PATH}/googletest/build)
link_directories(${GTEST_PATH}/googlemock/build)

# libgtest.a libpthread.a 를 포함시킨다.
set(TEST_FRAME_LIBS
  gtest
  pthread
)
 
######################
# build setting - coverage option을 추가한다.
######################
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} -coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -isystem .  -coverage ")
 

######################
# Unit Test setting
######################
set(UNIT_TEST_SRC_LIST
  ${CMAKE_SOURCE_DIR}/src/sum.cc
  ${CMAKE_SOURCE_DIR}/test/src/gtest_sum.cpp
)

# unit test 실행 target 을 만들때 지정된 source files를 이용해서 실행파일을 생성.
add_executable(${GTEST_EXE} ${UNIT_TEST_SRC_LIST})

# link library는 libgtest.a libpthread.a를 link한다.
target_link_libraries(${GTEST_EXE} ${TEST_FRAME_LIBS})
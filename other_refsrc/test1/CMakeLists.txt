# cmake 설명 : https://www.tuwlab.com/27234

# check minium version of cmake
cmake_minimum_required(VERSION 2.8.12)

# set project name
project(printsum)
 
include(FindPkgConfig)

# google test Path 설정
set(GTEST_PATH ~/sdetshare/workspace/gtest/googletest)

# 각각의 source file에서 #include의 header file을 찾을 directory목록을 찾는다. (-I option과 동일)
include_directories(${GTEST_PATH}/googletest/include ${GTEST_PATH}/googlemock/include) # google test 관련 include경로 지정

# test file에 대한 include 경로 지정
include_directories(${CMAKE_SOURCE_DIR}/src) # test file에 대한 include 경로 지정

# cmake file 에서 file을 다루기 위해서는 file() 을 사용한다. GLOB를 사용하면 file목록을 손쉽게 가공 가능 (file read/write/make folder/remove etc...)
file(GLOB_RECURSE SOURCES src/*.cc)

# Binary name을 printsum으로 설정한다.
set(BIN_NAME printsum)

# SRC_LIST에 source file list를 저장한다.
set(SRC_LIST ${SOURCES})
 

# compile option 설정 : https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html#Option-Summary (https://jangpd007.tistory.com/220)
# TARGET_COMPILE_OPTIONS ( app.out PUBLIC -g -Wall )를 사용해도 됨.
# -Wall : 미초기화 변수 warning.
# -rdynamic : Pass the flag -export-dynamic to the ELF linker, on targets that support it. This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of dlopen or to allow obtaining backtraces from within a program.
set(COMMON_CFLAGS "-Wall -funwind-tables -rdynamic") 

# -g : for debugging symbol -O : optimize option
set(COMMON_FLAGS "${COMMON_CFLAGS} -g -O0")

# C compile flag = common flag + CFlag
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")

# CXX compile flag : c++ 11 적용
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")

# Add Compile options - CMake 2.8.12 or newer
# Starting with CMake 3.3 you can also make this flag only apply to a specific language (e.g. only C or C++) using the strange generator expressions syntax:
# add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++14> $<$<COMPILE_LANGUAGE:C>:-std=c99>)
add_compile_options(-std=c++11)    # add_definitions(-std=c++0x) # CMake 2.8.11 or older

# 대상 소스 파일 목록을 SRC_LIST 변수로 지정하고, 이들로부터 out 실행파일(${BIN_NAME})을 생성
add_executable(${BIN_NAME} ${SRC_LIST})

# add_executable() 뒤에 target에 대한 multiple properties를 설정가능함.
set_target_properties(${BIN_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Target 링크시 포함할 라이브러리 목록을 지정합니다. 이 때, 라이브러리 파일명의 Prefix 및 Postfix는 제외하고 라이브러리 이름만 입력합니다. 
# (e.g. libxxx.a에서 xxx에 해당하는 부분만 입력) 컴파일러 옵션중 -l에 해당합니다. TARGET_LINK_LIBRARIES ( <Target_이름> <라이브러리> <라이브러리> ... )
target_link_libraries(${BIN_NAME})
 
# 'make install' 명령을 실행했을 때 무슨 동작을 수행할지를 지정합니다.
# ${PROJECT_BINARY_DIR} : build를 한 full path directory
# ${PROJECT_NAME} : project() 명령어로 지정한 이름
# ${DESTDIR} : make DESTDIR = /home/sdet install
install(
        FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        DESTINATION ${DESTDIR}/usr/bin
)

########################
# Unit test
# add_subdirectory(folder) 를 통해 지정된 folder에 cmake file을 만들어 주고 project(printsum) 도 동일하게 설정한다.
# 그러면 product code가 build되고 test folder에 cmake를 실행하여 test framework를 build 및 실행한다.
########################
add_subdirectory(test)
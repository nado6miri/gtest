CC = g++
GTEST_DIR=../googletest/googletest
GTEST_CXX_FLAGS= -isystem ${GTEST_DIR}/include -L${GTEST_DIR}/build -pthread -lgtest
DEFAULT_MAIN = main.cc

.PHONY : clean all

EXCUTABLE = sample1 sample2 sample3 sample4 sample5 sample6 sample7 sample8 sample9 sample10



all : $(EXCUTABLE)

sample1:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc $@.cc ${GTEST_CXX_FLAGS} 

sample2:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc $@.cc ${GTEST_CXX_FLAGS} 

sample3:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc ${GTEST_CXX_FLAGS} 

sample4:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc $@.cc ${GTEST_CXX_FLAGS} 

sample5:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc sample1.cc ${GTEST_CXX_FLAGS} 	

sample6:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc ${GTEST_CXX_FLAGS} 

sample7:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc ${GTEST_CXX_FLAGS} 

sample8:
	$(CC) -o $@ $(DEFAULT_MAIN) $@_unittest.cc ${GTEST_CXX_FLAGS} 

sample9:
	$(CC) -o $@ $@_unittest.cc ${GTEST_CXX_FLAGS} 

sample10:
	$(CC) -o $@ $@_unittest.cc ${GTEST_CXX_FLAGS} 


clean:
	rm -rf *.o ${EXCUTABLE}

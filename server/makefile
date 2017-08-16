OBJS = server.o validator.o screener.o router.o bitlib.o
TEST_OBJS = tests/validator_test.o bitlib.o validator.o
CC = g++
INCL = -I../include
THREAD = -pthread
LFLAGS = -Wall -std=c++11
CFLAGS = -Wall -std=c++11 -c

server : $(OBJS)
	$(CC) $(LFLAGS) $(INCL) $(OBJS) -o server $(THREAD)
bitlib.o : ../include/bitlib/bitlib.h ../include/bitlib/bitlib.cpp
	$(CC) $(CFLAGS) ../include/bitlib/bitlib.cpp
validator.o : validator.h validator.cpp
	$(CC) $(CFLAGS) $(INCL) validator.cpp
screener.o : screener.h screener.cpp
	$(CC) $(CFLAGS) $(INCL) screener.cpp
router.o : router.h router.cpp
	$(CC) $(CFLAGS) $(INCL) router.cpp
server.o : server.h server.cpp
	$(CC) $(CFLAGS) $(INCL) server.cpp

test : $(TEST_OBJS)
	$(CC) $(LFLAGS) $(INCL) $(TEST_OBJS) -o server -lboost_unit_test_framework
tests/validator_test.o : tests/validator_test.cpp
	$(CC) $(CFLAGS) $(INCL) -o tests/validator_test.o tests/validator_test.cpp

clean:
	\rm *.o server

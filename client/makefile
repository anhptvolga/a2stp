CC = g++

CFLAGS = -Wall -c -std=c++11
LFLAGS = -Wall -std=c++11

OBJS = bitlib.o client.o
TEST_OBJS = bitlib.o clientlib.o
DEPS = ../include/utils/const.h ../include/utils/su.h
TARGET = client

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o client

bitlib.o : ../include/bitlib/bitlib.h ../include/bitlib/bitlib.cpp $(DEPS)
	$(CC) $(CFLAGS) ../include/bitlib/bitlib.cpp

clientlib.o : client.h client.cpp $(DEPS)
	$(CC) $(CFLAGS) -DUNIT_TEST client.cpp -o clientlib.o

client.o : client.h client.cpp $(DEPS)
	$(CC) $(CFLAGS) client.cpp

dummy.o : dummy/dummy.h dummy/dummy.cpp client.o $(DEPS)
	$(CC) $(CFLAGS) dummy/dummy.cpp

test: clientlib.o bitlib.o test_client.cpp $(DEPS)
	$(CC) $(LFLAGS) $(TEST_OBJS) test_client.cpp -o test

clean:
	$(RM) *.o *~ client test *.out
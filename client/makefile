CC = g++

CFLAGS = -Wall -c -std=c++11
LFLAGS = -Wall -std=c++11

OBJS = bitlib.o client.o
DEPS = ../include/utils/const.h ../include/utils/su.h
TARGET = client

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o client

bitlib.o : ../include/bitlib/bitlib.h ../include/bitlib/bitlib.cpp $(DEPS)
	$(CC) $(CFLAGS) ../include/bitlib/bitlib.cpp

client.o : client.h client.cpp $(DEPS)
	$(CC) $(CFLAGS) client.cpp

clean:
	$(RM) *.o *~ client

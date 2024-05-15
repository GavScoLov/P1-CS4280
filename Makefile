CC      = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P1
OBJS    = main.o testScanner.o scanner.o #traversals.o

$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp testScanner.cpp testScanner.h scanner.cpp scanner.h
        $(CC) $(CFLAGS) -c main.cpp

clean:
        /bin/rm -f *.o $(TARGET)

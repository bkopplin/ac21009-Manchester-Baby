CC=g++
CFLAGS=-Wall -Wextra -g
HEADERS=binarynum.h processor.h mainstore.h processorregister.h BabyManager.hpp


main: main.cpp $(HEADERS)
	$(CC) $(CFLAGS) main.cpp -o main.out

test_binarynum: test_binarynum.cpp $(HEADERS)
	$(CC) $(CFLAGS) test_binarynum.cpp -o test_binarynum.out
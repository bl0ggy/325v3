CFLAGS=-std=c++0x
SOURCES=src/and.cpp src/logicgate.cpp src/main.cpp src/nand.cpp src/not.cpp src/or.cpp src/nor.cpp src/xor.cpp

all:
	g++ $(SOURCES) -o haha

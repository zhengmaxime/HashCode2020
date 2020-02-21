CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic -O3

SRC = main.cc
OBJ = ${SRC:.cc=.o}
BIN = main

all: ${OBJ}
	$(CXX) $(CXXFLAGS) ${OBJ} -o $(BIN)

clean:
	${RM} ${OBJ} $(BIN)

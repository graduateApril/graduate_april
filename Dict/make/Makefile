SRC = ../src
INCLUDE = ../include

CXXFLAGS = -g -O0 -Wall -Wextra -Werror=cpp \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -Wno-deprecated \
	   -I$(INCLUDE)

all: dict_example 
clean:
	rm -f april core

dict_example: dict.o $(SRC)/example.cpp 
	g++ $(CXXFLAGS) -o $@ $^
	
dict.o: $(SRC)/dict.cpp
	g++ -c $(CXXFLAGS) -o $@ $^

.PHONY: all clean

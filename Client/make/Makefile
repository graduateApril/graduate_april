MUDUO_DIRECTORY ?= $(HOME)/Tools/build/debug-install
#MUDUO_DIRECTORY ?= $(HOME)/Tools/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ../src
INCLUDE = ../include

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE) \
	   -I$(INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt

all: aprilclient 
clean:
	rm -f april core

aprilclient: $(SRC)/april.cpp april_client.o april_codec.o
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

april_client.o: $(SRC)/april_client.cpp april_codec.o
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	
april_codec.o: $(SRC)/april_codec.cpp $(INCLUDE)/april_codec.h
	g++ -c $(CXXFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: all clean

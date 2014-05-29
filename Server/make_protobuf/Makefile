MUDUO_DIRECTORY ?= $(HOME)/Tools/build/debug-install
#MUDUO_DIRECTORY ?= $(HOME)/Tools/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ../src
INCLUDE = ../include
DICT_INCLUDE = ../../Dict/include
DICT_SRC = ../../Dict/src

CXXFLAGS = -g -O0 -Wall -Wextra -Werror=cpp \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -Wno-deprecated \
	   -I$(MUDUO_INCLUDE) \
	   -I$(INCLUDE) \
	   -I$(DICT_INCLUDE) \
	   -I$(DICT_SRC)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt -lprotobuf -lz

all: april_protobuf
clean:
	rm -f april_protobuf april_protobuf_server.o april_protobuf_codec.o april_response.o *.log

april_protobuf: $(SRC)/april.cpp april_protobuf_server.o april_protobuf_codec.o $(INCLUDE)/april_response.pb.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

april_protobuf_server.o: $(SRC)/april_protobuf_server.cpp april_protobuf_codec.o april_response.o
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	
april_protobuf_codec.o: $(SRC)/april_protobuf_codec.cpp april_response.o 
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

april_response.o: $(INCLUDE)/april_response.pb.cpp $(INCLUDE)/april_response.pb.h
	g++ -c $(CSSFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

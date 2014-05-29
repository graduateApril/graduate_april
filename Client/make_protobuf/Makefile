MUDUO_DIRECTORY ?= $(HOME)/Tools/build/debug-install
#MUDUO_DIRECTORY ?= $(HOME)/Tools/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ../src
INCLUDE = ../include

CXXFLAGS = -g -O0 -Wall -Wextra -Werror=cpp \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE) \
	   -I$(INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt -lprotobuf -lz

all: aprilclient_protobuf
clean:
	rm -f aprilclient_protobuf april_protobuf_client.o april_protobuf_codec.o april_request.o april_response.o *.log

aprilclient_protobuf: $(SRC)/april.cpp april_protobuf_client.o april_protobuf_codec.o $(INCLUDE)/april_response.pb.cpp 
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

april_protobuf_client.o: $(SRC)/april_protobuf_client.cpp april_protobuf_codec.o 
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	
april_protobuf_codec.o: $(SRC)/april_protobuf_codec.cpp
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

april_request.o: $(INCLUDE)/april_request.pb.cpp $(INCLUDE)/april_request.pb.h
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

april_response.o: $(INCLUDE)/april_response.pb.cpp $(INCLUDE)/april_response.pb.h
	g++ -c $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

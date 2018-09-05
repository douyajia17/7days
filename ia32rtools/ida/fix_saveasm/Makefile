CC = gcc
CXX = g++
IDASDK = $(wildcard ../idasdk*)

CFLAGS += -Wall -Wno-sign-compare -fno-strict-aliasing -m32
CFLAGS += -I$(IDASDK)/include/ -D__IDP__ -D__PLUGIN__ -D__LINUX__
all: saveasm.plx

%.plx: %.cpp
	$(CXX) -shared -o $@ $(CFLAGS) $^ $(LDFLAGS)

clean:
	$(RM) saveasm.plx

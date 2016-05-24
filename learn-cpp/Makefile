EXEC = a.out
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

CXXFLAGS = -Wall -g# -std=c++11
LDFLAGS =

LD = g++
ifeq ($(shell which clang),)
CXX = g++
else
CXX = $(shell which clang)
endif

.PHONY: all clean rebuild cmake cmake-clean

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJS) : %.o:%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	-rm -f $(EXEC)
	-rm -f $(OBJS)

rebuild: clean all

cmake: build
	cd build && cmake ..
	echo "----"
	echo "Please execute `make' in build"

cmake-clean:
	-rm -rf build

build:
	mkdir -p $@

EXEC = a.out
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

CXXFLAGS = -Wall -g
LDFLAGS =

LD = g++
CXX = g++

.PHONY: all clean rebuild

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJS) : %.o:%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	-rm -f $(EXEC)
	-rm -f $(OBJS)

rebuild: clean all

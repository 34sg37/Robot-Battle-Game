CXX=g++
CXXFLAGS=-std=c++11 -Wall

SRCS=main.cpp Game.cpp Robots.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
EXECUTABLE=Program

all: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJS) $(EXECUTABLE)
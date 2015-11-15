CXX = clang++
# CXXFLAGS = -std=c++11 -pthread
CXXFLAGS = -std=c++11
LIBS = -lportaudio
SRCS = main.cpp  mixer.cpp  oscillator.cpp  sawtooth.cpp  sqump.cpp  triangle.cpp  utils.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = CPPPOP

.PHONY: depend clean

all: $(TARGET)
	@echo Boom! make some noise...

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o *~ $(TARGET)

depend: $(SRCS)
	makedepend $^



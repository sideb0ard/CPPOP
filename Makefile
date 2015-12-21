CXX = clang++
# CXXFLAGS = -std=c++11 -pthread
CXXFLAGS = -std=c++11 -pthread -Wall -Werror
LIBS = -lportaudio -lreadline
INC = -I/usr/local/include
SRCS = main.cpp  mixer.cpp  oscillator.cpp  sawtooth.cpp  fm.cpp  triangle.cpp  utils.cpp bpmrrr.cpp algae.cpp envelope.cpp
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



CXXFLAGS = -O2 -g -Wall -fmessage-length=0

SOURCES = abb.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = abb

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

CXX = g++
TARGET = superhero
SRCDIR = src
HEADDIR = includes
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRC:.cpp=.o)
CCFLAGS = -I$(HEADDIR) -Wall -g

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CCFLAGS) -o $@ $^

$(SRCDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -o $@ -c $< $(CCFLAGS)

.PHONY: clean cleaner

clean :
	@find $(SRCDIR)/ ! -name "tiny*" -and -name "*.o" -exec rm {} \;

cleaner :
	@rm $(TARGET)
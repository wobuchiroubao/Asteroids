SRCS ?= engine.cc game.cc
override OBJS = $(SRCS:.cc=.o)
NAME ?= game
CXX ?= g++
override CPPFLAGS +=
override CXXFLAGS +=
override LDFLAGS +=
override LDLIBS += -lSDL2

#############

all: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

clean:
	rm -f *.o $(NAME)

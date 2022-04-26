CC = gcc
CXX = g++
RM = rm -f

SRCS = example.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

all: example

example: $(OBJS)
	$(CXX) -o example $(OBJS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend

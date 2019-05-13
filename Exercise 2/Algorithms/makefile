COMP = g++-8.3.0

SHARED_OBJS = _314615600_a.so _314615600_b.so
OBJS = _314615600_a.o _314615600_b.o
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG -fPIC -lstdc++fs
CPP_LINK_FLAG = -shared

all: $(SHARED_OBJS)

_314615600_a.o: _314615600_a.cpp _314615600_a.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 

_314615600_a.so: _314615600_a.o
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^

_314615600_b.o: _314615600_b.cpp _314615600_b.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 

_314615600_b.so:  _314615600_b.o
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^
	
clean:
	rm -f $(OBJS) $(SHARED_OBJS)

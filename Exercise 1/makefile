COMP = g++-5.3.0
#put all your object files here
OBJS = #objects should be placed here! 
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp gameManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

player.o: player.cpp player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

parser.o: parser.cpp parser.h maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

maze.o: maze.cpp maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

gameManager.o: gameManager.cpp gameManager.h parser.h maze.h player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
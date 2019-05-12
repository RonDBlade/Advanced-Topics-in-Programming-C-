COMP = g++-8.3.0

OBJS = AlgorithmRegistration.o gameManager.o matchManager.o parser.o maze.o main.o
EXEC = match
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -ldl -export-dynamic#(-rdynamic) -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@ 
	

	
AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

gameManager.o: gameManager.cpp gameManager.h parser.h maze.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

matchManager.o: matchManager.cpp matchManager.h gameManager.h parser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
maze.o: maze.cpp maze.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

parser.o: parser.cpp parser.h maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

main.o: main.cpp matchManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
clean:
	rm -f $(OBJS) $(EXEC)

COMP = g++-8.3.0

OBJS = main.o AlgorithmRegistration.o gameManager.o matchManager.o parser.o
EXEC = match
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -ldl -export-dynamic#(-rdynamic) 

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@ 
	
AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

gameManager.o: gameManager.cpp gameManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

matchManager.o: matchManager.cpp matchManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
parser.o: parser.cpp parser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

main.o: main.cpp #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
clean:
	rm -f $(OBJS) $(EXEC)

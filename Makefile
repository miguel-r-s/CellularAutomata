GCC=g++
FLAGS=-Wall -std=c++11 -O3

# default builds the necessary object files
default: board.o

%: %.cpp board.o 
	$(GCC) $(FLAGS) -o $@.out board.o $<
	@echo "> Compilation terminated!"

board.o: board.cpp board.hpp global.hpp cell.hpp
	@echo "> Building object files."
	$(GCC) $(FLAGS) -c board.cpp

clean:
	@echo "> Removing object files."
	rm -f *.o
	@echo "> Removing executable files."
	rm -f *.out
	
cleanfiles:
	rm dataFiles/*.dat
	
clean2Dfiles:
	rm 2D/*.dat
	
cleanall:
	clean
	cleanfiles
	clean2Dfiles

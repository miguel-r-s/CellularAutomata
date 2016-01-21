GPP=g++
FLAGS=-Wall -std=c++11 -O3

%: %.cpp board.cpp board.hpp global.hpp cell.hpp
	$(GPP) $(FLAGS) -o $@.out board.cpp $<
	@echo "Compilation terminated!"

default:
	@echo "Please input sources"

clean:
	rm *.out
	
cleanfiles:
	rm dataFiles/*.dat
	
clean2Dfiles:
	rm 2D/*.dat
	
cleanall:
	clean
	cleanfiles
	clean2Dfiles
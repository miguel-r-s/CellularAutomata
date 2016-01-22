/*
	
	Creates a file in which each line has the number of iterations necessary for 
	the board to reach stability, for a board with a fixed size and a fixed initial number
	of occupied cells.
	
*/

#include <iostream>
#include <fstream>
#include "board.hpp"

#define DIRECTORY "2D_stability/"

using namespace std;
using namespace RuleStrings;

int main( void ) {
	
	srand(time(NULL));
	
	ofstream out;
	const int vertSize = 10;
	const int horiSize = 10;
	const int n_repetitions = 1E4;
	const double prob = 0.6;

	// Comment this loop and uncomment the "rule" line to run for a specific rule
	for( auto & rule : RuleStrings::rules ) { 
	//	Rule rule = LongLife_rule; 
		Board B( Board::SizeV{vertSize}, Board::SizeH{horiSize}, rule.second );
		
		out.open(DIRECTORY + rule.first + ".dat");
		for( int i = 0; i < n_repetitions; i++ ) {
			
			B.setRandom(prob*vertSize*horiSize);
			int steps =  B.stepsToStability();
			out << steps << endl;
		}
		cout << "Done with rule: " << rule.first << endl;
		out.close();
	}

	return 0;
}

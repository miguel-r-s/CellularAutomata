/*
	
	Analyses the relationship between the average STS (Steps to stability) and
	the initial occupation of the board.
*/

#include <iostream>
#include <fstream>
#include "board.hpp"

#define DIRECTORY "sts_vs_occupation/"

using namespace std;
using namespace RuleStrings;

int main( void ) {
	
	srand(time(NULL));
	
	ofstream out;
	const int sizeH = 8;
	const int sizeV = 8;
	const int minOccupation = 0;
	const int maxOccupation = sizeV*sizeH;
	const int n_repetitions = 1E4;
	
	// Comment this loop and uncomment the "rule" line to run for a specific rule
	for( auto & rule : RuleStrings::rules ) {
	//Rule rule = Amoeba_rule;
		
		cout << "Starting rule " << rule.first << endl;
		out.open(DIRECTORY + rule.first + "_sts_vs_occupation.dat");

		Board B( Board::SizeV{sizeV}, Board::SizeH{sizeH}, rule.second );
	
		for( unsigned int occupation = minOccupation; occupation <= maxOccupation; occupation++ ) {
			
			cout << "\tComputing for Occupation = " << occupation << endl;
			int count = 0;
			for( int i = 0; i < n_repetitions; i++ ) {
			
				B.setRandom(occupation);
				count += B.stepsToStability();
			}
			out << occupation << " " << static_cast<double>(count)/n_repetitions << endl;
		}
		cout << "Done..!" << endl;
		out.close();
	}
	
	return 0;
}

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <string>
#include "board.hpp"

#include "command_line_options.h"

using namespace std;
using namespace RuleStrings;

/* 
	This file exists to aid quick comparison 
	between performances of two branches.
 */

int main(int argc, char** argv){
	
	srand(time(NULL));

	const unsigned int num_iterations = 1E3;

	// Default values	
	unsigned int vertSize = 800;
	unsigned int horiSize = 400;
	double prob = 0.25;
	std::string ruleString = ConwaysLife_rulestring;

	Board B( Board::SizeV{vertSize}, Board::SizeH{horiSize}, ruleString);
	B.setRandom(prob*vertSize*horiSize);

	for( unsigned int i = 0; i < num_iterations && !B.isStable(); i++){
		B.setNext();
	}

	std::cout << B;
	return 0;
}
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <string>
#include "board.hpp"

#include "command_line_options.h"

using namespace std;
using namespace RuleStrings;

int main(int argc, char** argv){
	
	srand(time(NULL));

	// Default values	
	unsigned int vertSize = 200;
	unsigned int horiSize = 200;
	double prob = 0.25;
	std::string ruleString = ConwaysLife_rulestring;

	/* Choose size and occupation status */
	if( cmdOptionExists(argv, argv + argc, "-v") ){
		vertSize = atoi(getCmdOption(argv, argv + argc, "-v"));
	}
	if( cmdOptionExists(argv, argv + argc, "-h") ){
		horiSize = atoi(getCmdOption(argv, argv + argc, "-h"));
	}
	if( cmdOptionExists(argv, argv + argc, "-p") ){
		prob = atof(getCmdOption(argv, argv + argc, "-p"));
	}

	// Choose rule by name or by string directly
	if( cmdOptionExists(argv, argv + argc, "--rule-name") ){
		
		std::string ruleName = getCmdOption(argv, argv + argc, "--rule-name");
		for( auto& rule : RuleStrings::rules ){
			if(rule.first == ruleName){
				ruleString = rule.second;
				break;
			}
		}
	}
	if( cmdOptionExists(argv, argv + argc, "--rule-string") ){
		ruleString = getCmdOption(argv, argv + argc, "--rule-string");
	}

	Board B( Board::SizeV{vertSize}, Board::SizeH{horiSize}, ruleString);
	B.setRandom(prob*vertSize*horiSize);
	B.setStorage(false);

	const time_t time_start = time(0);
	const time_t max_time_seconds = 30;
	
	// Set next state for 30 seconds
	time_t new_time = time(0);
	int32_t num_iterations;

	for(num_iterations = 0; new_time - time_start < max_time_seconds; num_iterations++){
		
		B.setNext();
		new_time = time(0);
	}
	
	// Printing makes sure the computations are performed
	// i.e. printing makes it impossible for the compiler to entirely discard computations
	cout << B << endl;

	cout << float(num_iterations)/max_time_seconds << " iterations per second." << endl;
	return 0;
}
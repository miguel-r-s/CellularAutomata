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
	unsigned int vertSize = 20;
	unsigned int horiSize = 20;
	double prob = 0.6;
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
		for( auto & rule : RuleStrings::rules ){
			if(rule.first == ruleName){
				ruleString = rule.second;
				break;
			}
		}
	}
	if( cmdOptionExists(argv, argv + argc, "-r") ){
		ruleString = getCmdOption(argv, argv + argc, "-r");
	}

	Board B( Board::SizeV{vertSize}, Board::SizeH{horiSize}, ruleString);
	B.setRandom(prob*vertSize*horiSize);

	while(!B.isStable()){
		B.setNext();
		system("clear");
		std::cout << B;
		usleep(3E4);
	}

	return 0;
}
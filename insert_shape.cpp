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
	int shapeX = horiSize/2;
	int shapeY = vertSize/2;
	std::string shapeName = "Shapes/glider.txt";
	std::string ruleString = ConwaysLife_rulestring;

	/* Choose size and occupation status */
	if( cmdOptionExists(argv, argv + argc, "-v") ){
		vertSize = atoi(getCmdOption(argv, argv + argc, "-v"));
	}
	if( cmdOptionExists(argv, argv + argc, "-h") ){
		horiSize = atoi(getCmdOption(argv, argv + argc, "-h"));
	}
	if( cmdOptionExists(argv, argv + argc, "--shape-x") ){
		shapeX = atof(getCmdOption(argv, argv + argc, "--shape-x"));
	}
	if( cmdOptionExists(argv, argv + argc, "--shape-y") ){
		shapeY = atof(getCmdOption(argv, argv + argc, "--shape-y"));
	}
	if( cmdOptionExists(argv, argv + argc, "--shape-name") ){
		shapeName = getCmdOption(argv, argv + argc, "--shape-name");
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
	if( cmdOptionExists(argv, argv + argc, "--rule-string") ){
		ruleString = getCmdOption(argv, argv + argc, "--rule-string");
	}

	Board B( Board::SizeV{vertSize}, Board::SizeH{horiSize}, ruleString);
	B.insertShape(shapeName, Board::Row{shapeY}, Board::Col{shapeX});

	while(1){
		B.setNext();
		usleep(3E5);
		system("clear");
		std::cout << B;
	}

	return 0;
}
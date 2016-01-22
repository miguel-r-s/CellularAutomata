// distribution.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "global.hpp"
#include "board.hpp"
using namespace std;

const std::string get_time() {
	
	time_t currentTime;
	struct tm *localTime;
	std::stringstream ss;
	
	time( &currentTime );                   // Get the current time
	localTime = localtime( &currentTime );  // Convert the current time to the local time
	
	int Hour   = localTime->tm_hour;
	int Min    = localTime->tm_min;
	int Sec    = localTime->tm_sec;
	
	ss << Hour << "h" << Min << "m" << Sec << "s";

	return ss.str().c_str();
}
 

int main() {
	
	srand(time(NULL));
	const int numberOfRepetitions = 1E4;
	const int sizeMin = 2;
	const int sizeMax = 15;
	const int step = 1;
	
	//for( auto & rule : RuleStrings::rules ){

		Rule rule = Assimilation_rule;

		string rulestring = rule.second;
		string rulename = rule.first;
		string filename = "sts_vs_prob_vs_size/" + rulename + ".dat";
		         
		cout << "────────────────────────────────────────────────" << endl;
		cout << "Starting rule: " << rulename << " " << rulestring << endl;
		cout << "Output to: " << filename << endl;
		
		std::ofstream file;
		file.open(filename);
		
		for( unsigned int sqSize = sizeMin; sqSize <= sizeMax; sqSize++){ // Grid Size
		
			Board B( Board::SizeV{ sqSize }, Board::SizeH{ sqSize }, rulestring );
		
			for( int occupation = 1; occupation <= sqSize * sqSize; occupation += step){ // Occupation Status
			
				int counter = 0; 
				for(int iteration = 0; iteration < numberOfRepetitions; iteration++){
				
					B.setRandom(occupation);
					counter += B.stabilityPeriod();
				}

				file << sqSize << ' ' << occupation << ' ' << ( (double)counter/(double)numberOfRepetitions ) << std::endl;
			}
			std::cout << "Size " << sqSize << ": Done!" << std::endl;
		}
	
		file.close();
		
		cout << "Finished at " << get_time() << endl;
		cout << "────────────────────────────────────────────────" << endl;
	//}

	return 0;
}

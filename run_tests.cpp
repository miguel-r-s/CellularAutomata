#include <iostream>
#include <fstream>
#include <cassert>
#include "board.hpp"

struct TestCase_t {

	int sizeV;
	int sizeH;
	std::string rule_string;
};

struct  IterationCorrectnessTest_t {

	TestCase_t test_case;
	std::string problem_file;
	std::string solution_file;

	int num_iterations;
};

struct PeriodCorrectnessTest_t {

	TestCase_t test_case;
	std::string problem_file;

	int target;
};

std::ostream& operator << (std::ostream& os, const TestCase_t& tc) {
	return os << "(" << tc.sizeV << ", " << tc.sizeH << ", " << tc.rule_string << ")";
}

std::ostream& operator << (std::ostream& os, const IterationCorrectnessTest_t& ict) {
	os << "Problem : " << ict.problem_file << '\n'
	   << "Solution: " << ict.solution_file << '\n' 
	   << "Target  : " << ict.num_iterations << '\n'
	   << "Board   : " << ict.test_case << '\n';
	return os;
}

int main(int argc, char** argv) {

	/*

		1) Test some known start->end
		2) Test B(step=n) = B(step=n+stabilityPeriod-1), to guarantee the period is well calculated
		3) Output statistics on speed (conf/second).
	*/

	// 1) Test known start/end pair
	std::cout << "Testing iteration correctness" << std::endl;
	
	std::vector<IterationCorrectnessTest_t> iteration_test_cases {
		{{  3,   3,  ConwaysLife_rulestring}, "test_files/p1.dat", "test_files/p1-solution.dat", 1},
		{{  5,   5,  ConwaysLife_rulestring}, "test_files/line.dat", "test_files/line-solution.dat", 1},
		{{101, 101,  ConwaysLife_rulestring}, "test_files/glider.dat", "test_files/glider.dat", 404},
		{{25,   20,  ConwaysLife_rulestring}, "test_files/pentadecathlon.dat", "test_files/pentadecathlon.dat", 15},
		
		/* This is a particularly interesting test case, since it combines two oscillators with different periods.

		   Oscillator           Period
		   ---------------------------
		   Pentadecathlon           15
		   Line                      2
		   ---------------------------

			The stability period will be 30 since that is the Least Common Multiple of the 
			two periods.
		*/
		{{25,   46,  ConwaysLife_rulestring}, "test_files/pentadecathlonandline.dat", "test_files/pentadecathlonandline.dat", 30},
		
		/* This test is like the previous, except another figure with period 3 is added. 
		   The least common denominator is is still 30. 
		*/
		{{43,   46,  ConwaysLife_rulestring}, "test_files/pentadecathlonandlineandother.dat", "test_files/pentadecathlonandlineandother.dat", 30},
	};

	for(auto& test: iteration_test_cases) {

		std::ifstream problem_file (test.problem_file);
		std::ifstream solution_file(test.solution_file);
		
		Board b_problem ( Board::SizeV{test.test_case.sizeV}, Board::SizeH{test.test_case.sizeH}, test.test_case.rule_string);
		Board b_solution( Board::SizeV{test.test_case.sizeV}, Board::SizeH{test.test_case.sizeH}, test.test_case.rule_string);

		problem_file  >> b_problem;
		solution_file >> b_solution;

		for(int i = 0; i < test.num_iterations; ++i){
			b_problem.setNext();
		}

		if(b_problem == b_solution) {
			std::cout << "\e[32mTest passed!\n";
		}
		else {
			std::cout << "\e[31mTest failed\n";
		}

		std::cout << test << '\n';
		std::cout << "--------------------------------------\e[0m" << std::endl;
	}

	return 0;
}
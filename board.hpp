// board.hpp
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "global.hpp"
#include "cell.hpp"

class Board {

public:
	
	
	
	/*
		These structs are here to increase the readability of
		the subsequent code calling this class.
	
		Example:
			
			- Constructor: Board B( Board::SizeV{10}, Board::SizeH{15} )
			-     isAlive: B.isAlive( Board::Row{10}, Board::Col{15} ) 
	*/
	struct Row{int val;};
	struct Col{int val;};
	
	struct SizeV{unsigned int val;};  // Number of rows, size of the columns
	struct SizeH{unsigned int val;};  // Number of columns, size of the rows
	
	Board(SizeV, SizeH, std::string s = ConwaysLife_rulestring);
	Board(const Board&);
	~Board();
	
	bool isAlive(Row, Col) const;
	bool isStable() const;

	int stepsToStability();
	int stabilityPeriod(); // Evaluates the number of steps in the stability period. 
	
	void setRule(std::string);
	void setCellStatus(Row, Col, Cell::Status);
	void setAll(Cell::Status);
	void clearAll();
	void setRandom(int); // Expects number of occupied cells.
	void insertShape(std::string file_name, Row row, Col col);
	void setBoundary(Cell::Status);
	void setNext();
		
	//Assignment operator
	Board& operator=(Board);
	friend std::ostream& operator << (std::ostream&, const Board&);
	friend std::istream& operator >> (std::istream&, Board&);
	

private:
	
	typedef std::vector< std::vector< Cell > > Board_t;
	Board_t board;
		
	/*
		This unordered_map will store the hashes of each
	 	of the previous configurations of the board.
	*/
	std::unordered_map< std::string, int > hash_map;
	
	std::string rule;
	std::vector<int> survival;
	std::vector<int> birth;
	
	bool _isStable;
	
	int sizeV;  
	int sizeH;
	
	void storeHash();
	std::string configurationString() const ; 
	int countLivingNeighbours(Row, Col) const;
			
};

#endif
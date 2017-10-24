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
	
	void setRule(const std::string&);
	void setCellStatus(Row, Col, Cell::Status);
	void setAll(Cell::Status);
	void clearAll();
	void setRandom(int); // Expects number of occupied cells.
	void insertShape(std::string file_name, Row row, Col col);
	void setBoundary(Cell::Status);
	void setNext();
	void setStorage(bool on=true);
		
	//Assignment operator
	Board& operator=(Board);
	friend std::ostream& operator << (std::ostream&, const Board&);
	friend std::istream& operator >> (std::istream&, Board&);
	friend bool operator==(const Board&, const Board&);

private:
	
	/*
		Two boards are created for optimization purposes.
		One of them is the "current" board, the other is the "next" board.
		This prevents having to copy the board at each iteration.
	
		std::vector<bool> is a specialization of std::vector
	    that uses only one bit to represent each bool.
	*/
	std::vector<bool> board[2];
		
	/*
		This unordered_map will store the hashes of each
	 	of the previous configurations of the board if _should_store == true
	*/
	std::unordered_map< std::size_t, int > hash_map;
	
	std::string rule;
	std::vector<int> survival;
	std::vector<int> birth;
	
	bool _isStable;
	bool _should_store;

	bool _index; // Used to determine which of the boards is currently active

	int sizeV;  
	int sizeH;

	// Can only access the _next_ element from within 
	// the implementation of the class. The public 
	// implementation of setCellStatus only 
	void setCellStatus(Row, Col, Cell::Status, bool next);
	void storeHash();
	int countLivingNeighbours(Row, Col) const;
			
};

#endif
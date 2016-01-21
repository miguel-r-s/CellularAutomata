// board.cpp
#include <sstream>
#include <utility>
#include <fstream>
#include <algorithm>

#include "board.hpp"

#define ALIVE_CHAR 'O'
#define DEAD_CHAR  '-'

Board::Board(SizeV v, SizeH h, std::string ruleString){
	
	sizeV = v.val;
	sizeH = h.val;
	
	board.resize(sizeH, std::vector< Cell >( sizeV ));
	
	_isStable = false;
	setRule(ruleString);
}

Board::Board(const Board& B){
	
	sizeV = B.sizeV;
	sizeH = B.sizeH;
	
	board = B.board;
	_isStable = false;
	setRule(B.rule);
}


Board::~Board(){};

bool Board::isAlive(Row row, Col col) const { return board.at( col.val ).at( row.val ).isAlive(); }
bool Board::isStable() const { return _isStable; }

int Board::countLivingNeighbours(Row row, Col col) const {
	
	int num_living = 0;
	
	for(int i = -1; i <= 1; i++){
		for(int ii = -1; ii <= 1; ii++){
			
			if(!i && !ii) continue;
			
			
			/* Wrap around: This means if the cell being evaluated
			is in the boarders, the cells on the other side will count 
			as neighbours too.*/
			int row_number = ( row.val + i )  >= sizeV ? 0:
							 ( row.val + i )  < 0	   ? (sizeV - 1):
							 row.val + i;
				
				
			int col_number = ( col.val + ii ) >= sizeH ? 0: 
				             ( col.val + ii ) < 0	   ? (sizeH - 1):
				             col.val + ii;
				
			
			if( isAlive( Row{row_number}, Col{col_number} ) )
				num_living++;
			
		}	
	}
	
	return num_living;
}


/*
This function turns a given configuration of
the automaton into a string of 0 and 1
*/
std::string Board::configurationString() const {
	
	std::stringstream ss;
	
	for(int i = 0; i < sizeV; i++)
		for(int ii = 0; ii < sizeH; ii++)
			ss << ( isAlive( Row{i}, Col{ii} ) ? '1':'0' );
	
	return ss.str();
}

int Board::stepsToStability() {
	
	int step = 0;
	while( !isStable() ){
		setNext();
		step++;
	}
	return step;
}

int Board::stabilityPeriod() {
	
	/*
		
		In any finite cellular automaton, the pattern will repeat after a finite number of steps.
		This is because there is only a certain number of configurations the board
		can have. 
	
		Whe know we reached stability when the current configuration equals one previous configuration.
		This function returns the number of steps of a stability period.
	
		The minimum stability period will be 1. This means in a stable situation, B == next B.
		
	*/
	
	int step = stepsToStability();
	
	std::unordered_map< std::string, int >::const_iterator iter = hash_map.find( configurationString() );
	
	return (step - iter->second);
}

void Board::setRule(std::string userRule){
	
	/*
		userRule should be in the format S/B. (i.e. 23/3, 3579/2, /3, 4/,  etc...)
		S is the survival rule.
		B is the Birth rule.
	
		I still have to write some validation for this input.
	*/
	
	// Loading the rules into the corresponding vectors.
	rule = userRule;
	bool beyondSlash = false;
	survival.clear();
	birth.clear();
	for(int i = 0; i < static_cast<int>(rule.length()); i++){
		
		char c = rule[i];
		int cint = (int)c - (int)'0';
		
		if(c == '/'){
			beyondSlash=true;
			continue;
		}
		else if( cint < 0 || cint > 8 ){}
		else if(!beyondSlash) survival.push_back(cint);
		else if(beyondSlash)  birth.push_back(cint);
		else{}		
	}
}

void Board::setCellStatus(Row row, Col col, Cell::Status cs){

	board.at( col.val ).at( row.val ).status = cs;
}

void Board::setAll(Cell::Status cs){
	
	for(int i = 0; i < sizeV; i++){
		for(int ii = 0; ii < sizeH; ii++){
			setCellStatus( Row{i}, Col{ii}, cs );
		}
	}	
}

void Board::clearAll(){
	
	_isStable = false;
	hash_map.clear();
	setAll(Cell::Status::Dead);
}

void Board::setRandom(int numberOfLivingCells){

	int numberOfCells = sizeV * sizeH;
	if(numberOfLivingCells > numberOfCells)
		numberOfLivingCells = numberOfCells;
	
	double prob_alive = (double)numberOfLivingCells/numberOfCells;
	
	for(int i = 0; i < sizeV; i++){
		for(int ii = 0; ii < sizeH; ii++){
			double rnd = (double) rand()/(double)RAND_MAX;
			Cell::Status cs = (rnd < prob_alive) ? Cell::Status::Alive : Cell::Status::Dead;
			setCellStatus( Row{i}, Col{ii}, cs);
		}
	}
	
	_isStable = false;
	hash_map.clear();
}

void Board::insertShape(std::string file_name, Row row, Col col) {

	std::ifstream file(file_name);
	std::string line;
	int r = 0;
	while(file >> line) {
		for(int c = 0; c < static_cast<int>(line.length()); c++) {
			Cell::Status cs = (line[c] == ALIVE_CHAR) ? Cell::Status::Alive : Cell::Status::Dead;
			setCellStatus( Row{r + row.val}, Col{c + col.val}, cs );
		}
		r++;
	}

	file.close();
}

void Board::setBoundary(Cell::Status cs){
	
	// Horizontal Boundary 
	for(int i = 0; i < sizeH; i++){
		
		setCellStatus(Row{0}, 		Col{i}, cs);
		setCellStatus(Row{sizeV-1}, Col{i}, cs);
		
	}
	
	// Vertical Boundary
	for(int i = 0; i < sizeV; i++){
		
		setCellStatus(Row{i}, 		Col{0}, cs);
		setCellStatus(Row{i}, Col{sizeH-1}, cs);
		
	}	
}

void Board::setNext(){
	
	Board boardCopy(*this);
	
	// Calculate next Step
	for(int i = 0; i < sizeV; i++){
		for(int ii = 0; ii < sizeH; ii++){
			
			int N = boardCopy.countLivingNeighbours( Row{i} , Col{ii} );
			
			bool isAlive = ( boardCopy.isAlive( Row{i}, Col{ii} ));
			bool willSurvive = (std::find(survival.begin(), survival.end(), N) != survival.end());
			bool willBeBorn  = (std::find(birth.begin()	  , birth.end()	  , N) != birth.end());
				
			if(isAlive && !willSurvive ) 	 setCellStatus( Row{i}, Col{ii}, Cell::Status::Dead  );
			else if(!isAlive && willBeBorn ) setCellStatus( Row{i}, Col{ii}, Cell::Status::Alive );
			else {}
			
		}
	}
	
	storeHash();
}


void Board::storeHash(){
	
	/*
	
		This block helps to determine wether or not the present configuration has happened before.

			- Make hash of the configuration of the system.
			- Store the hash as the 'key'.
			- Compare each hashed configuration to  all the previous hashes.
			- If there is a match, we reached stability
	
		Unused features:
			
			- The variable 'index' will be used to determine the periodicty of the stability period.
	
	*/
	
	
	int index = hash_map.size() + 1; // The index will be as the 'next position in the hash table'
	
	std::string preHash = configurationString();
	
	if(hash_map.count(preHash) > 0) _isStable = true;
	else hash_map[preHash] = index;
	
}

Board& Board::operator=( Board b ){

	if( (sizeV != b.sizeV) || (sizeH != b.sizeH) ){
		std::cerr << "ERROR: Assignment is not possible."
				  << " Cannot assign boards with different sizes."
				  << std::endl;
		
		exit(-1);
	}
	
	board = b.board;

	return *this;
}

std::ostream& operator << (std::ostream& os, const Board& obj){
	
	for(int i = 0; i < obj.sizeV; i++){
		for(int ii = 0; ii < obj.sizeH; ii++){
			
			bool alive = obj.isAlive(Board::Row{i}, Board::Col{ii});
			os << ( alive ? ALIVE_CHAR:DEAD_CHAR ) << ' ';
		
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
	
}

std::istream& operator >> (std::istream& is, Board& obj){
	
	int sizeV, sizeH;
	
	std::cin >> sizeV >> sizeH;
	
	if(!std::cin)
		goto formating_error;
	
	for(int i = 0; i < obj.sizeV; i++){
		for(int ii = 0; ii < obj.sizeH; ii++){
			
			char c;
			Cell::Status CS;
			
			is >> c;
			
			if      ( c == ALIVE_CHAR ) CS = Cell::Status::Alive;
			else if ( c == DEAD_CHAR  ) CS = Cell::Status::Dead;
			else goto formating_error;
			
			
			obj.setCellStatus(Board::Row{i}, Board::Col{ii}, CS);
		}
	}
	
	return is;
		
formating_error:

	std::cerr << "This file is misformated!" << std::endl;
	obj.setAll(Cell::Status::Dead);
	return is;
	
}

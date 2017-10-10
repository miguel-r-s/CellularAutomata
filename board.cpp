// board.cpp
#include <sstream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <regex>

#include "board.hpp"

#define ALIVE_CHAR 'O'
#define DEAD_CHAR  '-'

Board::Board(SizeV v, SizeH h, std::string ruleString){
	
	sizeV = v.val;
	sizeH = h.val;
	
	board[0] = Board_t(sizeH, std::vector< Cell >( sizeV ));
	board[1] = Board_t(sizeH, std::vector< Cell >( sizeV ));

	_index = false;
	_isStable = false;
	_should_store = true;
	setRule(ruleString);
}

Board::Board(const Board& B){

	Board(SizeV{B.sizeV}, SizeH{B.sizeH}, B.rule);

	// Deep copy of vectors
	board[0] = B.board[0];
	board[1] = B.board[1];
}


Board::~Board(){};

bool Board::isAlive(Row row, Col col) const { return board[_index].at( col.val ).at( row.val ).isAlive(); }
bool Board::isStable() const { return _isStable; }

int Board::countLivingNeighbours(Row row, Col col) const {
	
	int num_living = 0;
	
	for(int i = -1; i <= 1; ++i){
		for(int ii = -1; ii <= 1; ++ii){
			
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
				++num_living;
			
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
	
	for(int i = 0; i < sizeV; ++i)
		for(int ii = 0; ii < sizeH; ++ii)
			ss << ( isAlive( Row{i}, Col{ii} ) ? '1':'0' );
	
	return ss.str();
}

int Board::stepsToStability() {
	
	int step = 0;
	while( !isStable() ){
		setNext();
		++step;
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

void Board::setRule(const std::string& userRule) {
	
	// Match rule with a regex, for input validation
	std::regex regex(R"(^([0-8]*)/([0-8]*)$)" );
	std::smatch match;
	std::regex_match(userRule, match, regex);

	// Check if the match was successful
	if( match.empty() ) {
		throw std::invalid_argument("[ERROR] " + userRule + " is not a valid rule.");
	}

	// Clear previous rules
	survival.clear();
	birth.clear();

	// match.str(1) is the survival rule
	for(const char c: match.str(1)){
		int i = std::atoi(&c);
		survival.push_back(i);
	} 

	// match.str(2) is the birth rule
	for(const char c: match.str(2)){
		int i = std::atoi(&c);
	 	birth.push_back(i);
	} 

	// Assign _rule_ to the string passed by the user.
	rule = userRule;
}

void Board::setCellStatus(Row row, Col col, Cell::Status cs, bool next){

	board[next ? !_index:_index].at( col.val ).at( row.val ).status = cs;
}

void Board::setCellStatus(Row row, Col col, Cell::Status cs){
	setCellStatus(row, col, cs, false);
}

void Board::setAll(Cell::Status cs){
	
	for(int i = 0; i < sizeV; ++i){
		for(int ii = 0; ii < sizeH; ++ii){
			setCellStatus( Row{i}, Col{ii}, cs);
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
	
	for(int i = 0; i < sizeV; ++i){
		for(int ii = 0; ii < sizeH; ++ii){
			double rnd = (double) rand()/(double)RAND_MAX;
			Cell::Status cs = (rnd < prob_alive) ? Cell::Status::Alive : Cell::Status::Dead;
			setCellStatus( Row{i}, Col{ii}, cs);
			setCellStatus( Row{i}, Col{ii}, cs, true);
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
		for(int c = 0; c < static_cast<int>(line.length()); ++c) {
			Cell::Status cs = (line[c] == ALIVE_CHAR) ? Cell::Status::Alive : Cell::Status::Dead;
			setCellStatus( Row{r + row.val}, Col{c + col.val}, cs );
		}
		++r;
	}

	file.close();
}

void Board::setBoundary(Cell::Status cs){
	
	// Horizontal Boundary 
	for(int i = 0; i < sizeH; ++i){
		
		setCellStatus(Row{0}, 		Col{i}, cs);
		setCellStatus(Row{sizeV-1}, Col{i}, cs);
		
	}
	
	// Vertical Boundary
	for(int i = 0; i < sizeV; ++i){
		
		setCellStatus(Row{i}, 		Col{0}, cs);
		setCellStatus(Row{i}, Col{sizeH-1}, cs);
		
	}	
}

void Board::setNext(){
	
	// Calculate next Step
	for(int i = 0; i < sizeV; ++i){
		for(int ii = 0; ii < sizeH; ++ii){
			
			int n = countLivingNeighbours( Row{i} , Col{ii} );
			
			bool is_alive = isAlive( Row{i}, Col{ii} );
			bool will_survive  = (std::find(survival.begin(), survival.end(), n) != survival.end());
			bool will_be_born  = (std::find(birth.begin()	,    birth.end(), n) != birth.end());
				
			if(is_alive && !will_survive ) 	    setCellStatus( Row{i}, Col{ii}, Cell::Status::Dead , true );
			else if(!is_alive && will_be_born ) setCellStatus( Row{i}, Col{ii}, Cell::Status::Alive, true );
			else setCellStatus( Row{i}, Col{ii}, board[_index].at(ii).at(i).status, true );
		}
	}
	
	_index = !_index;

	if( _should_store )
		storeHash();

}


void Board::setStorage(bool on) {

	// Enable/disable storage. 
	// Enable for stability analysis
	// Disable for increased speed
	_should_store = on;
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
	
	board[_index] = b.board[_index];

	return *this;
}

std::ostream& operator << (std::ostream& os, const Board& obj){
	
	for(int i = 0; i < obj.sizeV; ++i){
		for(int ii = 0; ii < obj.sizeH; ++ii){
			
			bool alive = obj.isAlive(Board::Row{i}, Board::Col{ii});
			os << ( alive ? ALIVE_CHAR:DEAD_CHAR ) << ' ';
		
		}
		os << '\n'; // New line, but avoid flushing (as std::endl would).
	}
	os << std::endl;
	return os;
	
}

std::istream& operator >> (std::istream& is, Board& obj){
	
	int indexV;
	std::string line;
	
	for( indexV = 0; std::getline(is, line); ++indexV ) {

		Cell::Status cs;
		
		// Remove spaces from the line, if there are any (they may appear for aesthetic purposes)
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());		

		int len = line.length();
		if( len != obj.sizeH )
			throw std::ios_base::failure("The automata in the file doesn't have the correct dimensions: (V,H)=(" + std::to_string(obj.sizeV) +  ", " + std::to_string(obj.sizeH) + ")");

		// Go through each character of the line
		for( int i = 0; i < len; ++i ) {
			char c = line.at(i);
			if      ( c == ALIVE_CHAR ) cs = Cell::Status::Alive;
			else if ( c == DEAD_CHAR  ) cs = Cell::Status::Dead;
			else throw std::ios_base::failure("File is misformatted (could not parse the board correctly)");
			obj.setCellStatus(Board::Row{indexV}, Board::Col{i}, cs);
		}
	}

	if( indexV != obj.sizeV ) {
		std::cout << indexV << " " << obj.sizeV << std::endl;
		throw std::ios_base::failure("File is misformatted (not enough lines in the automata)");
	}

	return is;	
}

bool operator==(const Board& lhs, const Board& rhs) {
	
	// Quick inexpensive tests
	if(lhs.sizeV != rhs.sizeV) return false;
	if(lhs.sizeH != rhs.sizeH) return false;

	// Check health status in each cell from lhs == rhs
	for(int i = 0; i < lhs.sizeV; ++i){
		for(int ii = 0; ii < lhs.sizeH; ++ii){

			if( lhs.isAlive(Board::Row{i}, Board::Col{ii}) != rhs.isAlive(Board::Row{i}, Board::Col{ii}) ) {
				return false;
			}
		}
	}

	return true;
}

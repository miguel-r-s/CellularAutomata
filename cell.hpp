// cell.hpp
#ifndef CELL_HPP
#define CELL_HPP

class Cell{
	
public:
	
	enum class Status{ Alive, Dead };
	Status status;
	
	Cell(){ status = Status::Dead; };
	~Cell(){};
	
	bool isAlive() const { return (status == Status::Alive); };
};

#endif
#include "LegalChecker.h"



bool LegalChecker::IsLegal(Position& position, Move& move){
    //if white move to a new position
    Position newPosition = Position(position, move);
    //return !newPosition.check;
	//std::cout << newPosition.PositionToFen() << std::endl;
    //bool checked =  newPosition.IsChecked(position.whiteTurn);
    //std::cout << "Checked: " << checked << std::endl;

    //white then being checked by black (during black's turn to move)
    return !newPosition.IsChecked(position.whiteTurn);
}
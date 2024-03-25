#include "LegalChecker.h"



bool LegalChecker::IsLegal(Position& position, unsigned short& move){
    //if white move to a new position
    Position newPosition = Position(position, move);
    //white then being checked by black (during black's turn to move)
    //if(ChessUtil::SimpleMoveToString(move) == "b5c6") {std::cout << newPosition.PositionToFullReport() << std::endl;}
    return !newPosition.IsChecked(position.whiteTurn);
}

void LegalChecker::AddMoveToList(Position& position, std::vector<unsigned short>& result, unsigned short move, bool needLegalCheck){
    if(!needLegalCheck){
        result.push_back(move);
    }else{
        if(LegalChecker::IsLegal(position, move)){
            //if(ChessUtil::SimpleMoveToString(move) == "b5c6") std::cout << "b5c6 legal" << std::endl;
            result.push_back(move);
        //std::cout << ChessUtil::SimpleMoveToString(move) << " is legal" << std::endl;
        }
        //if(ChessUtil::SimpleMoveToString(move) == "b5c6") std::cout << "b5c6 not legal" << std::endl;
    }
}
#include "LegalChecker.h"



bool LegalChecker::IsLegal(Position& position, unsigned short& move){
    //if white move to a new position
    Position newPosition = Position(position, move);
    //white then being checked by black (during black's turn to move)
    return !newPosition.IsChecked(position.whiteTurn);

    //position.MovePiece(move);
    //bool result = position.IsChecked(position.whiteTurn);
    //position.UnmovePiece();
    //return !result;
}

void LegalChecker::AddMoveToList(Position& position, std::vector<unsigned short>& result, unsigned short move, bool needLegalCheck){
    if(!needLegalCheck){
        result.push_back(move);
    }else{
        if(LegalChecker::IsLegal(position, move)){
            result.push_back(move);
        //std::cout << ChessUtil::SimpleMoveToString(move) << " is legal" << std::endl;
        }
    }
}
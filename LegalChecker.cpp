#include "LegalChecker.h"

bool LegalChecker::IsChecked(Position& position){
	int king = position.whiteTurn ? 4: 60;
	int kingsLocation = position.GetPieceLocation(king);
	std::vector<int> oppositeControlSquares = MoveGenerator::GenerateAllControlSquare(position, !position.whiteTurn);
	if(std::count(oppositeControlSquares.begin(), oppositeControlSquares.end(), kingsLocation)) {
		//std::cout << "Check+" << std::endl;
		return true;
	}else{
		//std::cout << "Not Check..." << std::endl;
		return false;
	}
}

bool LegalChecker::IsChecked(Position& position, bool white){
	int king = white ? 4: 60;
	int kingsLocation = position.GetPieceLocation(king);
	std::vector<int> oppositeControlSquares = MoveGenerator::GenerateAllControlSquare(position, !white);
	if(std::count(oppositeControlSquares.begin(), oppositeControlSquares.end(), kingsLocation)) {
		//std::cout << "Check+" << std::endl;
		return true;
	}else{
		//std::cout << "Not Check..." << std::endl;
		return false;
	}
}

bool LegalChecker::IsLegal(Position& position, Move& move){
    //if white move to a new position
    Position newPosition = Position(position, move);
    //white then being checked by black (during black's turn to move)
    bool getChecked = IsChecked(newPosition, position.whiteTurn);
    //the move is not legal
    return !getChecked;
}

std::vector<Move> LegalChecker::EliminateIllegalMoves(Position& position, std::vector<Move>& possibleMoves){
    std::vector<Move> legalMoves;
    for(Move move : possibleMoves){
        if(LegalChecker::IsLegal(position, move))legalMoves.emplace_back(move);
    }
    return legalMoves;
}
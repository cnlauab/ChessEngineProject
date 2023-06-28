#include "LegalChecker.h"

bool LegalChecker::IsCheckedAt(int target, Position& position, bool white){
    //Knight squares
    std::vector<int> knightSquare = ChessUtil::squareControlMap[target].GetKnightSquare();
    for(int i = 0; i < knightSquare.size(); i++){
        int piece = position.ReadPosition(knightSquare[i]);
        bool oppositeColor = white != ChessUtil::IsWhite(piece);
        bool isKnight = ChessUtil::IsKnight(piece);
        if(isKnight && oppositeColor){
            //std::cout << "Knight Check " << targets[i] << std::endl;
            return true;
        }
    }

    //Sliding squares
    for(int i = 0; i < 8; ++i){
        std::vector<int> slidingSquare = ChessUtil::squareControlMap[target].GetSlidingSquare(i);
        if(slidingSquare.size() == 0) continue;
        if(!position.TargetIsEmpty(slidingSquare[0]) && ChessUtil::IsKing(position.ReadPosition(slidingSquare[0])) && white != ChessUtil::IsWhite(position.ReadPosition(slidingSquare[0]))) {
            //std::cout << "King at " << target << " King Check " << square << std::endl;
            return true;
        }
        for(int j = 0; j < slidingSquare.size(); j++){
            int piece = position.ReadPosition(slidingSquare[j]);
            bool occupied = !position.TargetIsEmpty(slidingSquare[j]);
            bool oppositeColor = white != ChessUtil::IsWhite(piece);
            if(occupied && !oppositeColor) break;
            if(occupied && oppositeColor){
                if(i>=0 && i<=3){
                    if((ChessUtil::IsRook(piece) || ChessUtil::IsQueen(piece))) {
                        //std::cout << "Rook or Queen Check " << square << std::endl;
                        return true;
                    }
                    break;
                }else{
                    if((ChessUtil::IsBishop(piece) || ChessUtil::IsQueen(piece))) {
                        //std::cout << "Bishop or Queen Check " << square << std::endl;
                        return true;
                    }
                    break;
                }
            }
        }
    }

    //Pawn squares
    std::vector<int> pawnSquare = ChessUtil::squareControlMap[target].GetPawnSquare(white);
    for(int i = 0; i < pawnSquare.size(); i++){
        int piece = position.ReadPosition(pawnSquare[i]);
        bool oppositeColor = white != ChessUtil::IsWhite(piece);
        bool isPawn = ChessUtil::IsPawn(piece);
        if(oppositeColor && isPawn){
            //std::cout << "Pawn Check " << square1 << std::endl;
            return true;
        }
    }

    return false;
}

bool LegalChecker::IsChecked(Position& position){
	int king = position.whiteTurn ? 4: 60;
	int kingsLocation = position.GetPieceLocation(king);
    return LegalChecker::IsCheckedAt(kingsLocation, position, position.whiteTurn);
}

bool LegalChecker::IsChecked(Position& position, bool white){
	int king = white ? 4: 60;
	int kingsLocation = position.GetPieceLocation(king);
    return LegalChecker::IsCheckedAt(kingsLocation, position, white);
}

bool LegalChecker::IsLegal(Position& position, Move& move){
    //if white move to a new position
    Position newPosition = Position(position, move);
    //white then being checked by black (during black's turn to move)
    bool getChecked = IsChecked(newPosition, position.whiteTurn);
    //the move is not legal
    //std::cout << "getChecked: " << getChecked << std::endl;
    return !getChecked;
}

std::vector<Move> LegalChecker::EliminateIllegalMoves(Position& position, std::vector<Move>& possibleMoves){
    std::vector<Move> legalMoves;
    for(Move move : possibleMoves){
        if(LegalChecker::IsLegal(position, move))legalMoves.emplace_back(move);
    }
    return legalMoves;
}
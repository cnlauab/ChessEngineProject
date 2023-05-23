#include "LegalChecker.h"

bool LegalChecker::IsCheckedAt(int target, Position& position, bool white){
    //Knight squares
	int targets[8] = { target - 10, target - 17, target - 15, target - 6, target + 6, target + 15, target + 17, target + 10 };
	for (int i = 0; i < 8; i++)
	{
		if (targets[i] > 63 || targets[i] < 0) continue;
		if (i == 0 || i == 1) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(target);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(target);
			if (lefter && lower) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
                    std::cout << "Knight Check " << targets[i] << std::endl;
                    return true;
                }
            }
		}
		else if (i == 2 || i == 3) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(target);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(target);
			if (righter && lower) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
                    std::cout << "Knight Check " << targets[i] << std::endl;
                    return true;
                }
            }
		}
		else if (i == 4 || i == 5) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(target);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(target);
			if (lefter && higher) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
                    std::cout << "Knight Check " << targets[i] << std::endl;
                    return true;
                }
            }
		}
		else if (i == 6 || i == 7) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(target);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(target);
			if (righter && higher) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
                    std::cout << "Knight Check " << targets[i] << std::endl;
                    return true;
                }
            }
		}
	}
    //Sliding squares
    for(int i = 0; i < 8; ++i){
        int offset = ChessUtil::offsets[i];
		int square = target + offset;
		bool outOfBound = ChessUtil::SquareOutbound(target, square, i);
        int counter = 0;
		while (!outOfBound) {
            //std::cout << offset << " Sliding Check " << position.position[square] << " at " << square << std::endl;
            if(counter == 0)counter++;
			if(i>=0 && i<=3){
                if((ChessUtil::IsRook(position.position[square]) || ChessUtil::IsQueen(position.position[square])) && white != ChessUtil::IsWhite(position.position[square])) {
                    std::cout << "Rook or Queen Check " << square << std::endl;
                    return true;
                }
                if(counter == 1 && ChessUtil::IsKing(position.position[square]) && white != ChessUtil::IsWhite(position.position[square])) {
                    std::cout << "King Check " << square << std::endl;
                    return true;
                }
                if(!position.TargetIsEmpty(square)) break;
            }else{
                if((ChessUtil::IsBishop(position.position[square]) || ChessUtil::IsQueen(position.position[square])) && white != ChessUtil::IsWhite(position.position[square])) {
                    std::cout << "Bishop or Queen Check " << square << std::endl;
                    return true;
                }
                if(counter == 1 && ChessUtil::IsKing(position.position[square]) && white != ChessUtil::IsWhite(position.position[square])) {
                    std::cout << "King Check " << square << std::endl;
                    return true;
                }
                if(!position.TargetIsEmpty(square)) break;
            }
			square += offset;
			outOfBound = ChessUtil::SquareOutbound(target, square, i);
		}
    }
    //Pawn squares
    int square1 = 99;
    int square2 = 99;
    if(white){
        if(ChessUtil::GetFile(target) != 0) square1 = target + 7;
        if(ChessUtil::GetFile(target) != 7) square2 = target + 9;
    }else{
        if(ChessUtil::GetFile(target) != 0) square1 = target - 9;
        if(ChessUtil::GetFile(target) != 7) square2 = target - 7;
    }
    int piece1 = position.ReadPosition(square1);
    int piece2 = position.ReadPosition(square2);
    if(!ChessUtil::IsEmpty(square1) && ChessUtil::IsPawn(position.ReadPosition(square1)) && !ChessUtil::IsWhite(position.ReadPosition(square1))) {
        std::cout << "Pawn Check " << square1 << std::endl;
        return true;
    }
    if(!ChessUtil::IsEmpty(square2) && ChessUtil::IsPawn(position.ReadPosition(square2)) && !ChessUtil::IsWhite(position.ReadPosition(square2))) {
        std::cout << "Pawn Check " << square2 << std::endl;
        return true;
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
    return !getChecked;
}

std::vector<Move> LegalChecker::EliminateIllegalMoves(Position& position, std::vector<Move>& possibleMoves){
    std::vector<Move> legalMoves;
    for(Move move : possibleMoves){
        if(LegalChecker::IsLegal(position, move))legalMoves.emplace_back(move);
    }
    return legalMoves;
}
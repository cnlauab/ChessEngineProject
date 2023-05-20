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
                    return true;
                }
            }
		}
		else if (i == 2 || i == 3) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(target);
			bool lower = ChessUtil::GetRank(targets[i]) < ChessUtil::GetRank(target);
			if (righter && lower) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
                    return true;
                }
            }
		}
		else if (i == 4 || i == 5) {
			bool lefter = ChessUtil::GetFile(targets[i]) < ChessUtil::GetFile(target);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(target);
			if (lefter && higher) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
                    return true;
                }
            }
		}
		else if (i == 6 || i == 7) {
			bool righter = ChessUtil::GetFile(targets[i]) > ChessUtil::GetFile(target);
			bool higher = ChessUtil::GetRank(targets[i]) > ChessUtil::GetRank(target);
			if (righter && higher) {
                if(ChessUtil::IsKnight(position.position[targets[i]]) && white != ChessUtil::IsWhite(position.position[targets[i]])){
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
		while (!outOfBound) {
			square += offset;
			if(i>=0 && i<=3){
                if((ChessUtil::IsRook(position.position[targets[i]]) || ChessUtil::IsQueen(position.position[targets[i]])) && white != ChessUtil::IsWhite(position.position[targets[i]])) return true;
                if(!position.TargetIsEmpty(square)) break;
            }else{
                if((ChessUtil::IsBishop(position.position[targets[i]]) || ChessUtil::IsQueen(position.position[targets[i]])) && white != ChessUtil::IsWhite(position.position[targets[i]])) return true;
                if(!position.TargetIsEmpty(square)) break;
            }
			outOfBound = ChessUtil::SquareOutbound(target, square, i);
		}
    }
    //Pawn squares
    //King squares

    return false;
}

bool LegalChecker::IsChecked(Position& position){
	int king = position.whiteTurn ? 4: 60;
	int kingsLocation = position.GetPieceLocation(king);
    return LegalChecker::IsCheckedAt(kingsLocation, position, position.whiteTurn);
	//std::vector<int> oppositeControlSquares = MoveGenerator::GenerateAllControlSquare(position, !position.whiteTurn);
	//if(std::count(oppositeControlSquares.begin(), oppositeControlSquares.end(), kingsLocation)) {
	//	//std::cout << "Check+" << std::endl;
	//	return true;
	//}else{
	//	//std::cout << "Not Check..." << std::endl;
	//	return false;
	//}
}

bool LegalChecker::IsChecked(Position& position, bool white){
	int king = white ? 4: 60;
	int kingsLocation = position.GetPieceLocation(king);
    return LegalChecker::IsCheckedAt(kingsLocation, position, white);
	//std::vector<int> oppositeControlSquares = MoveGenerator::GenerateAllControlSquare(position, !white);
	//if(std::count(oppositeControlSquares.begin(), oppositeControlSquares.end(), kingsLocation)) {
	//	//std::cout << "Check+" << std::endl;
	//	return true;
	//}else{
	//	//std::cout << "Not Check..." << std::endl;
	//	return false;
	//}
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
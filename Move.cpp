#include "Move.h"

Move::Move()
{
	Move::from = 99;
	Move::to = 99;
	Move::piece = 99;
	Move::promotionType = ' ';

	Move::takenPiece = 99;
	Move::check = false;
	Move::checkMate = false;
}

Move::Move(std::string uci){
	Move::from = 99;
	Move::to = 99;
	Move::piece = 99;
	Move::promotionType = ' ';

	Move::takenPiece = 99;
	Move::check = false;
	Move::checkMate = false;
	if(uci.length() < 4) return;

	Move::from  = ChessUtil::GetSquareFromFileRank(ChessUtil::GetFileFromChar(uci[0]),ChessUtil::GetRankFromChar(uci[1]));
	Move::to = ChessUtil::GetSquareFromFileRank(ChessUtil::GetFileFromChar(uci[2]),ChessUtil::GetRankFromChar(uci[3]));
	Move::promotionType = (char)toupper(uci[5]);
}

Move::Move(short starting, short target)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = 99;
	Move::promotionType = ' ';

	Move::takenPiece = 99;
	Move::check = false;
	Move::checkMate = false;

	//std::cout << type  << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << std::endl;
	//std::cout << toString() << std::endl;
}

Move::Move(short starting, short target, char promotionType)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = 99;
	Move::promotionType = promotionType;

	Move::takenPiece = 99;
	Move::check = false;
	Move::checkMate = false;
	Move::rankAmbiguity = false;
	Move::fileAmbiguity = false;

	//std::cout << type << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << " promoting to " << promotionType << std::endl;
	//std::cout << toString() << std::endl;
}

void Move::UpdateCheck(bool check, bool checkMate){
	Move::check = check;
	Move::checkMate = checkMate;
}


void Move::UpdateAmbiguity(bool rankAmbiguity, bool fileAmbiguity){
	Move::rankAmbiguity = rankAmbiguity;
	Move::fileAmbiguity = fileAmbiguity;
}

bool Move::IsShortCastling(){
	return ChessUtil::IsKing(piece) && to - from == 2;
}

bool Move::IsLongCastling(){
	return ChessUtil::IsKing(piece) && to - from == -2;
}

std::string Move::toSimpleString()
{
	if (isEmpty()) return "Move is Empty...";

	std::string result = "";
	result += ChessUtil::SquareToString(from);
	result += ChessUtil::SquareToString(to);
	if(promotionType != 99)result += (char)tolower(promotionType);

	return result;
}

std::string Move::toString()
{
	if (isEmpty()) return "Move is Empty...";

	std::string result = "";
	char type = (piece != 99) ? toupper(ChessUtil::GetPieceType(piece)) : ' ';

	//result += type + ChessUtil::SquareToString(from) + " to " + ChessUtil::SquareToString(to) + " promoting to " + promotionType;
	if(IsShortCastling()){
		result += "O-O";
	}else if(IsLongCastling()){
		result += "O-O-O";
	}else{
		if(type != 'P') result += type;
		//result += ChessUtil::SquareToString(from);
		if((type == 'P' && takenPiece != 99) || fileAmbiguity) result += ChessUtil::GetFileChar(from);
		if(rankAmbiguity) result += ChessUtil::GetRankChar(from);
		if(takenPiece != 99) result += 'x';
		result += ChessUtil::SquareToString(to);
		if(promotionType != ' ') {
			result += '=';
			result += promotionType;
		}
	}
	if(check) {
		result += '+';
	}else if(checkMate){
		result += '#';
	}

	return result;
}

bool Move::isEmpty()
{
	return from == 99 || to == 99;
}

bool Move::operator==(const Move& rhs)
{
	return from == rhs.from && to == rhs.to && piece == rhs.piece && promotionType == rhs.promotionType;
}

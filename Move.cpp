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

Move::Move(int piece, int starting, int target)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = piece;
	Move::promotionType = ' ';

	Move::takenPiece = 99;
	Move::check = false;
	Move::checkMate = false;

	//std::cout << type  << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << std::endl;
	std::cout << toString() << std::endl;
}

Move::Move(int piece, int starting, int target, char promotionType)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = piece;
	Move::promotionType = promotionType;

	Move::takenPiece = 99;
	Move::check = false;
	Move::checkMate = false;

	//std::cout << type << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << " promoting to " << promotionType << std::endl;
	std::cout << toString() << std::endl;
}

std::string Move::toString()
{
	if (isEmpty()) return "Move is Empty...";

	std::string result = "";
	char type = toupper(ChessUtil::GetPieceType(piece));

	//result += type + ChessUtil::SquareToString(from) + " to " + ChessUtil::SquareToString(to) + " promoting to " + promotionType;
	
	if(type != 'P') result += type;
	result += ChessUtil::SquareToString(from);
	if(takenPiece != 99) result += 'x';
	result += ChessUtil::SquareToString(to);
	if(promotionType != ' ') result += '=' + promotionType;
	if(check) {
		result += '+';
	}else if(checkMate){
		result += '#';
	}

	return result;
}

bool Move::isEmpty()
{
	return from == 99 || to == 99 || piece == 99;
}

bool Move::operator==(const Move& rhs)
{
	return from == rhs.from && to == rhs.to && piece == rhs.piece && promotionType == rhs.promotionType;
}

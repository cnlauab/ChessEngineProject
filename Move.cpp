#include "Move.h"

Move::Move()
{
	Move::from = 99;
	Move::to = 99;
	Move::piece = 99;
	Move::promotionType = ' ';
}

Move::Move(int piece, int starting, int target)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = piece;
	Move::promotionType = ' ';

	char type = ChessUtil::GetPieceType(piece);
	std::cout << type  << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << std::endl;
}

Move::Move(int piece, int starting, int target, char promotionType)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = piece;
	Move::promotionType = promotionType;

	char type = ChessUtil::GetPieceType(piece);
	std::cout << type << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << " promoting to " << promotionType << std::endl;
}

std::string Move::toString()
{
	if (isEmpty()) return "Move is Empty...";

	std::string result = "";
	char type = ChessUtil::GetPieceType(piece);
	//result += type + "(" + std::to_string(piece) + ")" + ChessUtil::SquareToString(from) + " to " + ChessUtil::SquareToString(to) + " promoting to " + promotionType + "\n";
	result += type + ChessUtil::SquareToString(from) + " to " + ChessUtil::SquareToString(to) + " promoting to " + promotionType;
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

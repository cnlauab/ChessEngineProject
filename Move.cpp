#include "Move.h"

Move::Move()
{
}

Move::Move(int piece, int starting, int target)
{
	Move::from = starting;
	Move::to = target;
	Move::piece = piece;

	char type = ChessUtil::GetPieceType(piece);
	std::cout << type  << ChessUtil::SquareToString(starting) << " to " << ChessUtil::SquareToString(target) << std::endl;
}

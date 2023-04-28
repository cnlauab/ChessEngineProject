#include "Position.h"

Position::Position()
{
	for (int i = 0; i < 64; i++) {
		if (i < 16 || i >47) {
			position[i] = i;
		}
		else {
			position[i] = 99;
		}
	}
}

Position::Position(std::string fen)
{
	Parser parser;
	parser.FenToPosition(fen, position);
	for (int i = 0; i < 64; ++i) {
		int piece = position[i];
		if (piece != 99) {
			pieceLocation[piece] = i;
		}
	}
}

int Position::GetPieceLocation(int piece)
{
	return pieceLocation[piece];
}

bool Position::TargetIsEmpty(int target) const
{
	return position[target] == 99;
}

bool Position::TargetIsOppositeColor(int piece, int target) const
{
	if (position[target] == 99) return false;
	return ChessUtil::IsWhite(position[target]) != ChessUtil::IsWhite(piece);
}

bool Position::EnpassantSquareIsOppositeColor(int piece) const
{
	if (enPassantSquare == 99) return false;
	bool enPassantSquareIsWhite = enPassantSquare < 32;
	return enPassantSquareIsWhite != ChessUtil::IsWhite(piece);
}

std::string Position::PositionToFen()
{
	return std::string();
}

void Position::MovePiece(int startSquare, int endSquare)
{
	position[endSquare] = position[startSquare];
	position[startSquare] = 99;
}

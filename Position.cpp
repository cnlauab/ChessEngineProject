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

void Position::MovePiece(Move& move)
{
	move.takenPiece = position[move.to];
	position[move.to] = position[move.from];
	position[move.from] = 99;
	if(move.takenPiece != 99) pieceLocation[move.takenPiece] = 99;
	pieceLocation[position[move.to]] = move.to;

	//if (ChessUtil::IsPawn(move.piece)) {
	//	if (whiteTurn) {
	//		if (move.to == enPassantSquare) {
	//			pieceLocation[position[move.to - 8]] = 99;
	//			position[move.to - 8] = 99;
	//		}
	//		if (move.to - move.from == 16) {
	//			
	//		}
	//	}
	//	else {
	//		if (move.to == enPassantSquare) {
	//			pieceLocation[position[move.to + 8]] = 99;
	//			position[move.to + 8] = 99;
	//		}
	//		if (move.to - move.from == -16) {
	//
	//		}
	//	}
	//}
	//if (ChessUtil::IsKing(move.piece)) {
	//	if (move.to - move.from == 2) {//K
	//		if (whiteTurn) {
	//
	//		}
	//		else {
	//
	//		}
	//	}
	//	else if (move.to - move.from == -3){ //Q
	//		if (whiteTurn) {
	//
	//		}
	//		else {
	//
	//		}
	//	}
	//}

}

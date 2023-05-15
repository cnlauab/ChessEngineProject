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

Position::Position(Position& currPosition, Move& move){
	whiteTurn = currPosition.whiteTurn;
	enPassantSquare = currPosition.enPassantSquare;
	halfmove = currPosition.halfmove;
	fullmove = currPosition.fullmove;
	for(int i = 0; i < 64; ++i){
		position[i] = currPosition.position[i];
	}
	pieceLocation = currPosition.pieceLocation;
	castlingQuota = currPosition.castlingQuota;

	MovePiece(move);
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
	//Update Clock
	halfmove++;
	if(!whiteTurn)fullmove++;
	//Update Board
	move.takenPiece = position[move.to];
	position[move.to] = position[move.from];
	position[move.from] = 99;
	if(move.takenPiece != 99) {
		pieceLocation[move.takenPiece] = 99;
		halfmove = 0;
	}
	pieceLocation[position[move.to]] = move.to;
	//Piece Specific Update
	if (ChessUtil::IsPawn(move.piece)) {
		halfmove = 0;
		if (whiteTurn) {
			if (move.to == enPassantSquare) {
				pieceLocation[position[move.to - 8]] = 99;
				position[move.to - 8] = 99;
			}
			if (move.to - move.from == 16) {
				enPassantSquare = move.from + 8;
			}
		}
		else {
			if (move.to == enPassantSquare) {
				pieceLocation[position[move.to + 8]] = 99;
				position[move.to + 8] = 99;
			}
			if (move.to - move.from == -16) {
				enPassantSquare = move.from - 8;
			}
		}
	}else{
		if(enPassantSquare != 99) enPassantSquare = 99;
	}
	if (ChessUtil::IsKing(move.piece)) {
		if (move.to - move.from == 2) {
			if (whiteTurn && castlingQuota['K']) {
				castlingQuota['K'] = false;
			}
			else if(!whiteTurn && castlingQuota['k']) {
				castlingQuota['k'] = false;
			}
		}
		else if (move.to - move.from == -3){
			if (whiteTurn && castlingQuota['Q']) {
				castlingQuota['Q'] = false;
			}
			else if(!whiteTurn && castlingQuota['q']) {
				castlingQuota['q'] = false;
			}
		}
	}
	if (ChessUtil::IsRook(move.piece)) {
		if(move.piece == 0 && castlingQuota['Q']){
			castlingQuota['Q'] = false;
		}else if(move.piece == 7 && castlingQuota['K']){
			castlingQuota['K'] = true;
		}else if(move.piece == 56 && castlingQuota['q']){
			castlingQuota['q'] = true;
		}else if(move.piece == 63 && castlingQuota['k']){
			castlingQuota['k'] = true;
		}
	}
	//Update Opposite Turn
	whiteTurn = !whiteTurn;
}

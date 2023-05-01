#pragma once
#include <vector>;
#include <cctype>;

#include "Position.h"
#include "Move.h"
#include "ChessUtil.h"

class MoveGenerator {
public:
	Move ExtractMove(char pieceType, int target, int file, int rank, bool white, std::vector<Move>& moves);
	std::vector<Move> ExtractMovesByPieceType(char pieceType, bool white, std::vector<Move>& moves);
	std::vector<Move> ExtractMovesByTargetSquare(int target, std::vector<Move>& moves);
	std::vector<Move> ExtractMovesByAmbiguity(int file, int rank, std::vector<Move>& moves);

	std::vector<Move> GenerateAllPossibleMoves(Position& position);
	std::vector<Move> GeneratePossibleMoves(int& piece, Position& position);
	std::vector<Move> GenerateSlidingMoves(int& piece, Position& position);
	std::vector<Move> GenerateKnightMoves(int& piece, Position& position);
	std::vector<Move> GeneratePawnMoves(int& piece, Position& position);
	std::vector<Move> GenerateKingMoves(int& piece, Position& position);

	std::vector<Move> GenerateCastlingMoves(int& piece, Position& position);

	std::vector<int> GenerateSlidingControlSquare(int& piece, Position& position);
	std::vector<int> GenerateKnightControlSquare(int& piece, Position& position);
	std::vector<int> GeneratePawnControlSquare(int& piece, Position& position);
	std::vector<int> GenerateKingControlSquare(int& piece, Position& position);

	bool PieceMatchTurn(int piece, Position& position);
private:
	int offsets[8] = { -1,1,-8,8,-9,-7,7,9 };
	bool SquareOutbound(int startingSquare, int targetSquare, int offsetType);
};
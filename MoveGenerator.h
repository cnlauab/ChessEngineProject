#pragma once
#include <vector>
#include <cctype>

#include "Position.h"
#include "Move.h"
#include "ChessUtil.h"
#include "LegalChecker.h"

class MoveGenerator {
public:
	static Move ExtractMove(char pieceType, short target, short file, short rank, bool white, char promotionType, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByPieceType(char pieceType, bool white, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByTargetSquare(short target, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByAmbiguity(short file, short rank, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByPromotionType(char promotionType, std::vector<Move>& moves);

	static std::vector<Move> GenerateAllPossibleMoves(Position& position);
	static std::vector<Move> GeneratePossibleMoves(short& piece, Position& position);
	static std::vector<Move> GenerateSlidingMoves(short& piece, Position& position);
	static std::vector<Move> GenerateKnightMoves(short& piece, Position& position);
	static std::vector<Move> GeneratePawnMoves(short& piece, Position& position);
	static std::vector<Move> GenerateKingMoves(short& piece, Position& position);

	static bool PieceMatchTurn(short piece, Position& position);
};
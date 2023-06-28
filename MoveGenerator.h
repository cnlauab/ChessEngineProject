#pragma once
#include <vector>
#include <cctype>

#include "Position.h"
#include "Move.h"
#include "ChessUtil.h"
#include "LegalChecker.h"

class MoveGenerator {
public:
	static Move ExtractMove(char pieceType, int target, int file, int rank, bool white, char promotionType, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByPieceType(char pieceType, bool white, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByTargetSquare(int target, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByAmbiguity(int file, int rank, std::vector<Move>& moves);
	static std::vector<Move> ExtractMovesByPromotionType(char promotionType, std::vector<Move>& moves);

	static std::vector<Move> GenerateAllPossibleMoves(Position& position);
	static std::vector<Move> GeneratePossibleMoves(int& piece, Position& position);
	static std::vector<Move> GenerateSlidingMoves(int& piece, Position& position);
	static std::vector<Move> GenerateKnightMoves(int& piece, Position& position);
	static std::vector<Move> GeneratePawnMoves(int& piece, Position& position);
	static std::vector<Move> GenerateKingMoves(int& piece, Position& position);

	static std::vector<int> GenerateAllControlSquare(Position& position, bool white);
	static std::vector<int> GenerateControlSquare(int& piece, Position& position);
	static std::vector<int> GenerateSlidingControlSquare(int& piece, Position& position);
	static std::vector<int> GenerateKnightControlSquare(int& piece, Position& position);
	static std::vector<int> GeneratePawnControlSquare(int& piece, Position& position);
	static std::vector<int> GenerateKingControlSquare(int& piece, Position& position);

	static bool PieceMatchTurn(int piece, Position& position);
};
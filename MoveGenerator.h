#pragma once
#include <vector>
#include <cctype>

#include "Position.h"
#include "ChessUtil.h"
#include "LegalChecker.h"

class MoveGenerator {
public:
	static unsigned short ExtractMove(char pieceType, short target, short file, short rank, bool white, char promotionType, std::vector<unsigned short>& moves, Position& position);
	static std::vector<unsigned short> ExtractMovesByPieceType(char pieceType, bool white, std::vector<unsigned short>& moves, Position& position);
	static std::vector<unsigned short> ExtractMovesByTargetSquare(short target, std::vector<unsigned short>& moves);
	static std::vector<unsigned short> ExtractMovesByAmbiguity(short file, short rank, std::vector<unsigned short>& moves);
	static std::vector<unsigned short> ExtractMovesByPromotionType(char promotionType, std::vector<unsigned short>& moves);

	static std::vector<unsigned short> GenerateAllPossibleMoves(Position& position);
	
	static void AddPawnMoves(Position& position, std::vector<unsigned short>& moves, short start, short target, bool capture);

	//New
	static void KingMoves(std::vector<unsigned short>& moves, Position& position);
	static void KnightMoves(std::vector<unsigned short>& moves, Position& position);
	static void SlidingMoves(std::vector<unsigned short>& moves, Position& position);
	static void PawnMoves(std::vector<unsigned short>& moves, Position& position);
};
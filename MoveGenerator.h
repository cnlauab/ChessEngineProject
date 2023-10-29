#pragma once
#include <vector>
#include <cctype>

#include "Position.h"
#include "Move.h"
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
	static std::vector<unsigned short> GeneratePossibleMoves(short& piece, Position& position);
	static std::vector<unsigned short> GenerateSlidingMoves(short& piece, Position& position);
	static std::vector<unsigned short> GenerateKnightMoves(short& piece, Position& position);
	static std::vector<unsigned short> GeneratePawnMoves(short& piece, Position& position);
	static std::vector<unsigned short> GenerateKingMoves(short& piece, Position& position);

	static std::vector<unsigned short> GenerateMovesWhenChecked(Position& position);
	static std::vector<unsigned short> GenerateMovesByEvading(Position& position);
	static std::vector<unsigned short> GenerateMovesByCapturing(Position& position);
	static std::vector<unsigned short> GenerateMovesByBlocking(Position& position);

	static bool PieceMatchTurn(short piece, Position& position);

	static std::vector<unsigned short> (*MoveGenerationByType[6]) (short&, Position&);
};
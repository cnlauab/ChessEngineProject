#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>

#include "SquareControl.h"

class ChessUtil {
public:
    static std::unordered_map<short, char> pieceMapping;
    static std::unordered_map<short, short> pieceScoreMapping;
	static std::unordered_map<short, int> pieceValueMapping;
    static char GetPieceType(short piece);

	static char file[8];
	static char rank[8];
	static short offsets[8];
	static short midGameScoreMap[64];
	static short endGameScoreMap[64];
	static short checkScore;

	static std::unordered_map <std::string, short> squareToIndexMapping;

	static SquareControl squareControlMap[64];
	static std::unordered_map<char, unsigned short> promotionTypeMap;

	static short GetRank(short square);
	static short GetFile(short square);
	static char GetRankChar(short square);
	static char GetFileChar(short square);
	static std::string SquareToString(short square);
	static short StringToSquare(std::string squareString);
	static short GetRankFromChar(char rank);
	static short GetFileFromChar(char file);
	static short GetSquareFromFileRank(short file, short rank);
	static bool SquareOutbound(short startingSquare, short targetSquare, short offsetType);

	static bool IsEmpty(short piece);
	static bool IsWhite(short piece);
	static bool IsPawn(short piece);
	static bool IsQueen(short piece);
	static bool IsBishop(short piece);
	static bool IsKnight(short piece);
	static bool IsKing(short piece);
	static bool IsRook(short piece);

	static bool IsLightSquare(short square);

	static unsigned short SimpleMove(short from, short to, char promotionType = 'Q');
	static short GetFrom(unsigned short move);
	static short GetTo(unsigned short move);
	static char GetPromotionType(unsigned short move);
	static std::string SimpleMoveToString(unsigned short move);
	static unsigned short UCIToMove(std::string uci);
};
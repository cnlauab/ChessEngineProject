#pragma once
#include <algorithm>
#include <unordered_map>
#include <string>

class ChessUtil {
public:
    static std::unordered_map<int, char> pieceMapping;
    static char GetPieceType(int piece);

	static char file[8];
	static char rank[8];
	static int offsets[8];
	static std::unordered_map <std::string, int> squareToIndexMapping;
	static int GetRank(int square);
	static int GetFile(int square);
	static char GetRankChar(int square);
	static char GetFileChar(int square);
	static std::string SquareToString(int square);
	static int StringToSquare(std::string squareString);
	static int GetRankFromChar(char rank);
	static int GetFileFromChar(char file);
	static bool SquareOutbound(int startingSquare, int targetSquare, int offsetType);

	static bool IsEmpty(int piece);
	static bool IsWhite(int piece);
	static bool IsPawn(int piece);
	static bool IsQueen(int piece);
	static bool IsBishop(int piece);
	static bool IsKnight(int piece);
	static bool IsKing(int piece);
	static bool IsRook(int piece);
};
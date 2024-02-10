
#pragma once
#include <climits>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "SquareControl.h"
#include "ChessUtil.h"

class BitUtil{
public:
    static const unsigned long long firstRank = 255ULL;
    static const unsigned long long secondRank = 65280ULL;
    static const unsigned long long seventhRank = 71776119061217280ULL;
    static const unsigned long long eighthRank = 18374686479671623680ULL;
    static const unsigned long long aFile = 72340172838076673ULL;
    static const unsigned long long bFile = 144680345676153346ULL;
    static const unsigned long long gFile = 4629771061636907072ULL;
    static const unsigned long long hFile = 9259542123273814144ULL;

    static const unsigned long long darkSquares = 12273903644374837845ULL;
    static const unsigned long long lightSquares = 6172840429334713770ULL;

	static std::unordered_map<char, int> pieceBitboardIndexMapping;
	static char bitboardIndexPieceMapping[6];
	static std::unordered_map<unsigned long long, short> bitToSquareMap;
    static std::unordered_map<char, unsigned long long> castleBlockingBits;
    static std::unordered_map<char, unsigned long long> friendlyCastleBlockingBits;

	static std::string bitboardToString(unsigned long long bitboard);
	static std::vector<short> getBitPositions(unsigned long long bitboard);
    static short getNumberOnBits(unsigned long long bitboard);

    static unsigned long long knightControlBits(unsigned long long knightbits);
    static unsigned long long pawnControlBits(unsigned long long pawnbits, bool white);
    static unsigned long long kingControlBits(unsigned long long kingbit);

    static unsigned long long GetFileBit(short file);
    static unsigned long long GetRankBit(short rank);

    static unsigned long long GetMagicKey(unsigned long long allPieces, short square, bool diagonal);

    static bool AllBitsOnSameRank(unsigned long long bits);
    static bool AllBitsOnSameFile(unsigned long long bits);

    private:
    
};

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ChessUtil.h"

class Bitboards {
    public:
        unsigned long long whiteBitboards[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
        unsigned long long blackBitboards[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};

        Bitboards();
        Bitboards(std::string fen);
        Bitboards(const Bitboards& other);

        unsigned long long allWhiteBitboard();
        unsigned long long allBlackBitboard();

        unsigned long long allEmptySquareBitboard();

        bool isEmpty(short square);
        bool hasWhitePiece(short square);
        int GetPieceTypeFromSquare(short square);
        void MoveBit(short from, short to, bool whiteTurn);

        std::string BitboardsToString();
};
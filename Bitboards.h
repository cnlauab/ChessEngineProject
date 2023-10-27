
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ChessUtil.h"
#include "BitUtil.h"

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
        void EnpassantMoveBit(short to, bool whiteTurn);
        void CastlingMoveBit(short to);
        void PromotionMoveBit(short to, short promotionType, bool whiteTurn);

        unsigned long long controlledBits(bool white);

        std::string BitboardsToString();
};
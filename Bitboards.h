
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ChessUtil.h"
#include "BitUtil.h"
#include "MagicUtil.h"

class Bitboards {
    public:
        unsigned long long whiteBitboards[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
        unsigned long long blackBitboards[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
        unsigned long long pinnedBitboard = 0ULL;
        unsigned long long checkedBitboard = ~0Ull;
        std::unordered_map<short,unsigned long long> pinnedRays;//square,ray
        
        Bitboards();
        Bitboards(std::string fen);
        Bitboards(const Bitboards& other);

        unsigned long long allWhiteBitboard();
        unsigned long long allBlackBitboard();
        unsigned long long getBitboard(bool white);

        unsigned long long allEmptySquareBitboard();
        unsigned long long GetPieceBitboard(bool white, short index);

        short KingLocation(bool white);

        bool isEmpty(short square);
        bool hasWhitePiece(short square);
        int GetPieceTypeFromSquare(short square);
        bool hasBothColorBishop(bool white);

        void MoveBit(short from, short to, bool whiteTurn);
        void EnpassantMoveBit(short to, bool whiteTurn);
        void CastlingMoveBit(short to);
        void PromotionMoveBit(short to, short promotionType, bool whiteTurn);

        void PutBackTakenPiece(short to, int type, bool whiteTurn);
        void ReverseEnpassantMoveBit(short to, bool whiteTurn);
        void ReverseCastlingMoveBit(short to);
        void ReversePromotionMoveBit(short to, short promotionType, bool whiteTurn);

        unsigned long long controlledBits(bool white);
        unsigned long long slidingControlBits(bool white, short square, short typeIndex, bool includeKing = true, bool includeFriendly = false);
        std::array<short, 2> checkedAt(bool white);

        std::string BitboardsToString();
        std::string ToFen();
};
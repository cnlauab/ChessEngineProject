
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ChessUtil.h"

class Bitboards {
    public:
        unsigned long long whiteBitboards[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};
        unsigned long long blackBitboards[6] = {0ULL,0ULL,0ULL,0ULL,0ULL,0ULL};

        Bitboards(std::string fen);

        unsigned long long allWhiteBitboard();
        unsigned long long allBlackBitboard();
};
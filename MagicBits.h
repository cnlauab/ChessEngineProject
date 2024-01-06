#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm> 
#include <utility> 

#include "SquareControl.h"
#include "ChessUtil.h"
#include "BitUtil.h"

class MagicBits{
    public :
        std::unordered_map<unsigned long long, unsigned long long> magicRook[64];
        std::unordered_map<unsigned long long, unsigned long long> magicBishop[64];

        MagicBits();
        MagicBits(std::string input);

        unsigned long long GetRookMagic(short square, unsigned long long key);
        unsigned long long GetBishopMagic(short square, unsigned long long key);
        unsigned long long GetQueenMagic(short square, unsigned long long rookKey, unsigned long long bishopKey);
};
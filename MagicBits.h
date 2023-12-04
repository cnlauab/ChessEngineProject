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
        std::unordered_map<unsigned long long, unsigned long long> importantBits;
        //std::unordered_map<unsigned long long, unsigned long long> emptyBits;

        MagicBits();
        MagicBits(std::string input);

};
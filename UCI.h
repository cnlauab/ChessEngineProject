#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
#include "Position.h"
#include "Evaluation.h"
#include "ChessUtil.h"

using namespace std;
class UCI {
public:
    static void SelfPlay();
    static void UCILoop();
    static Position ParsePosition(std::string line);
    
};
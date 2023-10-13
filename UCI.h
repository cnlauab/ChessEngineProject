#pragma once
#include <iostream>
#include <string>
#include "Debug.h"
#include "Position.h"
#include "Move.h"

using namespace std;
class UCI {
public:
    static void UCILoop();
    static Position ParsePosition(std::string line);
    
};
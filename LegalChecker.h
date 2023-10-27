#pragma once

#include <iostream>
#include "Position.h"

class LegalChecker {
public :
    static bool IsLegal(Position& position, Move& move);
};
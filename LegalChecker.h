#pragma once

#include <iostream>
#include "Position.h"

class LegalChecker {
public :
    static bool IsLegal(Position& position, unsigned short& move);
    static void AddMoveToList(Position& position, std::vector<unsigned short>& result, unsigned short move, bool needLegalCheck = false);
};
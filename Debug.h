#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include "BoardRenderer.h"
#include "Position.h"

class Debug {
public:
    static void UCILog(std::string message, bool receiving);
    static void GameLog(Position& position);
    static void ClearLog();
};


#pragma once
#include <string>
#include <unordered_map>
#include "ChessUtil.h"
#include "Position.h"
#include "State.h"

class BoardRenderer {
public:
	std::string positionToString(const Position& position);
};

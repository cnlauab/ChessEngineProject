
#pragma once
#include <string>
#include <unordered_map>
#include "ChessUtil.h"
#include "Position.h"
#include "State.h"

class BoardRenderer {
public:
	static std::string positionToString(const Position& position);
};

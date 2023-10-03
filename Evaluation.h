
#pragma once
#include <queue>
#include <unordered_map>
#include <chrono>

#include "Node.h"
#include "Position.h"
#include "MoveGenerator.h"

class Evaluation{
public:
    static Move Evaluate(Position& position);
    static Node* ConstructTree(Node* root, int level);
    static void DeleteTree(Node* root);

    static void BFS(Node* root);
    static short minimax(Node* node, int depth, bool maxingPlayer);
};
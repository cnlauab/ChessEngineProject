#pragma once
#include <vector>

#include "Position.h"
#include "Move.h"

class Node{
    public:
        float score;
        Position* position;

        Node* parentNode;
        std::vector<Node*> childrenNodes;

        Node(Position* pos);
        Node(Node* parent, Position* pos);

        ~Node();
};
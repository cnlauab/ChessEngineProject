#pragma once
#include <vector>

#include "Position.h"
#include "Move.h"

class Node{
    public:
        short score;
        Position* position;

        Node* parentNode;
        std::vector<Node*> childrenNodes;

        unsigned short bestMove;

        Node(Position* pos);
        Node(Node* parent, Position* pos);

        ~Node();

        void UpdateScore();
};
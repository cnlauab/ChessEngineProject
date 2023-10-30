#pragma once
#include <vector>

#include "Position.h"

class Node{
    public:
        short score;
        Position* position;

        Node* parentNode;
        std::vector<Node*> childrenNodes;

        unsigned short bestMove = 0;

        Node(Position* pos);
        Node(Node* parent, Position* pos);
        
        Node(std::string fen);
        Node(Node* parent, unsigned short move);

        ~Node();

        void UpdateScore();
};
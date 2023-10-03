#include "Node.h"

Node::Node(Position* pos){
    position = pos;
    score = position->CalculateScore();
}

Node::Node(Node* parent, Position* pos){
    parentNode = parent;
    position = pos;
    score = position->CalculateScore();
}

Node::~Node(){
}
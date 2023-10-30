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

Node::Node(std::string fen){
    position = new Position(fen);
    score = position->CalculateScore();
}

Node::Node(Node* parent, unsigned short move){
    parentNode = parent;
    position = new Position(*parent->position,move);
    score = position->CalculateScore();
}

Node::~Node(){
    if(position != nullptr){
        //std::cout << "Deleting Position..." << position << std::endl;
        delete position;
    }
}

void Node::UpdateScore(){
    score = position->CalculateScore();
}
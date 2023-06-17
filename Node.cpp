#include "Node.h"

Node::Node(Position* pos){
    position = pos;
}

Node::Node(Node* parent, Position* pos){
    parentNode = parent;
    position = pos;
}

Node::~Node(){
    
}
#include "Evaluation.h"

float Evaluation::Eval(Position& position){
    return 1.0;
}

Node* Evaluation::ConstructTree(Node* root, int level){
    Position* currPosition = root->position;
    std::vector<Move> possibleMoves = MoveGenerator::GenerateAllPossibleMoves(*currPosition);
    for(int i = 0; i < possibleMoves.size(); ++i){
        Position* newPosition = new Position(*currPosition, possibleMoves[i]);
        Node* childNode = new Node(root, newPosition);
        root->childrenNodes.emplace_back(childNode);
        if(level > 1){
            ConstructTree(childNode, level-1);
        }
    }
    //std::cout << "Level: " << level << " Move generated: " << root->childrenNodes.size() << std::endl;
    return root;
}

void Evaluation::DeleteTree(Node* node){
    if(node->childrenNodes.size() > 0){
        for(auto child : node->childrenNodes){
            DeleteTree(child);
        }
    }
    delete node->position;
    delete node;
}

void Evaluation::BFS(Node* root){
    std::queue<Node*> queue;
    std::queue<int> levelQueue;
    std::vector<Node*> visited;
    int level = 0;
    std::unordered_map<int,int> resultMap;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    Node* currentNode = root; 
    do{
        for(Node* child : currentNode->childrenNodes){
            queue.push(child);
            levelQueue.push(level + 1);
        }

        visited.push_back(currentNode);
        currentNode = queue.front();
        queue.pop();

        level = levelQueue.front();
        resultMap[levelQueue.front()] += 1;
        levelQueue.pop();

    }while(queue.size() > 0 || currentNode->childrenNodes.size() > 0);

    for (auto const& item : resultMap) {
        std::cout<< "Level " << item.first << ": " << item.second <<std::endl;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[Milliseconds]" << std::endl;
    
}

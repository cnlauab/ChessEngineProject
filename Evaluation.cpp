#include "Evaluation.h"

Move Evaluation::Evaluate(Position& position){
	Node* root = new Node(&position);
	Evaluation::ConstructTree(root, 3);
    minimax(root, 10, position.whiteTurn);
    Move bestMove = root->bestMove;
    //Evaluation::DeleteTree(root);
    return bestMove;
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

    std::unordered_map<int,int> epMap;
    std::unordered_map<int,int> castleMap;
    std::unordered_map<int,int> promotionMap;
    std::unordered_map<int,int> captureMap;
    std::unordered_map<int,int> checkMap;
    std::unordered_map<int,int> doubleCheckMap;
    std::unordered_map<int,int> discoverCheckMap;
    std::unordered_map<int,int> checkmateMap;
    
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
        if(currentNode->position->ep) epMap[levelQueue.front()] += 1;
        if(currentNode->position->castle) castleMap[levelQueue.front()] += 1;
        if(currentNode->position->promotion) promotionMap[levelQueue.front()] += 1;
        if(currentNode->position->capture) captureMap[levelQueue.front()] += 1;
        if(currentNode->position->check) checkMap[levelQueue.front()] += 1;
        if(currentNode->position->discoverCheck) discoverCheckMap[levelQueue.front()] += 1;
        if(currentNode->position->doubleCheck) doubleCheckMap[levelQueue.front()] += 1;
        //if(currentNode->childrenNodes.size() == 0) checkmateMap[levelQueue.front()] += 1;
        if(currentNode->position->checkmate) checkmateMap[levelQueue.front()] += 1;
        levelQueue.pop();

        //if(currentNode->position->discoverCheck) {
        //    std::cout << currentNode->position->PositionToFen() << "|| Prev Move: " << currentNode->position->prevMove.toString() << std::endl;
        //}

    }while(queue.size() > 0 || currentNode->childrenNodes.size() > 0);

    for (auto const& item : resultMap) {
        std::cout<< "Level " << item.first << ": " << item.second << "\t"
        << " \tCaptures: " << captureMap[item.first] 
        << " \tE.p.: " << epMap[item.first] 
        << " \tCastles: " << castleMap[item.first] 
        << " \tPromotions: " << promotionMap[item.first] 
        << " \tChecks: " << checkMap[item.first] 
        << " \tDiscovery Checks: " << discoverCheckMap[item.first] 
        << " \tDouble Checks: " << doubleCheckMap[item.first] 
        << " \tCheckmates: " << checkmateMap[item.first] 
        <<std::endl;
    }
}

short Evaluation::minimax(Node* node, int depth, bool maxingPlayer){
    if(depth == 0 || node->childrenNodes.size() == 0){
        return node->score;
    }

    if(maxingPlayer){
        short maxEval = -9999;
        for(Node* child : node->childrenNodes){
            short eval = minimax(child, depth - 1, false);
            if(eval > maxEval){
                maxEval = eval;
                node->bestMove = child->position->prevMove;
            }
        }
        return maxEval;
    }else{
        short minEval = 9999;
        for(Node* child : node->childrenNodes){
            short eval = minimax(child, depth - 1, true);
            if(eval < minEval){
                minEval = eval;
                node->bestMove = child->position->prevMove;
            }
        }
        return minEval;
    }
}
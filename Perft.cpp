#include "Perft.h"

Perft::Perft(std::string line){

}

Perft::Perft(int depth) : depth(depth), nodes(0), captures(0), enpassant(0), castles(0), promotions(0), checks(0), discoveryChecks(0), doubleChecks(0), checkMates(0){}

Perft::Perft(int depth, int nodes, int captures, int enpassant, int castles, int promotions, int checks, int discoveryChecks, int doubleChecks, int checkMates) : depth(depth), nodes(nodes), captures(captures), enpassant(enpassant), castles(castles), promotions(promotions), checks(checks), discoveryChecks(discoveryChecks), doubleChecks(doubleChecks), checkMates(checkMates){}

Perft::Perft(Perft& other){
    nodes = other.nodes;
    depth = other.depth;
    captures = other.captures;
    enpassant = other.enpassant;
    castles = other.castles;
    promotions = other.promotions;
    checks = other.checks;
    discoveryChecks = other.discoveryChecks;
    doubleChecks = other.doubleChecks;
    checkMates = other.checkMates;
}

Perft::Perft(Perft&& other){
    nodes = other.nodes;
    depth = other.depth;
    captures = other.captures;
    enpassant = other.enpassant;
    castles = other.castles;
    promotions = other.promotions;
    checks = other.checks;
    discoveryChecks = other.discoveryChecks;
    doubleChecks = other.doubleChecks;
    checkMates = other.checkMates;
}

Perft& Perft::operator=(Perft&& other){
    nodes = other.nodes;
    depth = other.depth;
    captures = other.captures;
    enpassant = other.enpassant;
    castles = other.castles;
    promotions = other.promotions;
    checks = other.checks;
    discoveryChecks = other.discoveryChecks;
    doubleChecks = other.doubleChecks;
    checkMates = other.checkMates;

    return *this;
}

void Perft::Add(bool captures_, bool enpassant_, bool castles_, bool promotions_, bool checks_, bool discoveryChecks_, bool doubleChecks_, bool checkMates_){
    nodes += 1;
    captures += captures_;
    enpassant += enpassant_;
    castles += castles_;
    promotions += promotions_;
    checks += checks_;
    discoveryChecks += discoveryChecks_;
    doubleChecks += doubleChecks_;
    checkMates += checkMates_;
}

void Perft::Add(Perft& others){
    nodes += others.nodes;
    captures += others.captures;
    enpassant += others.enpassant;
    castles += others.castles;
    promotions += others.promotions;
    checks += others.checks;
    discoveryChecks += others.discoveryChecks;
    doubleChecks += others.doubleChecks;
    checkMates += others.checkMates;
}

bool Perft::Equals(Perft& others){
    return depth == others.depth &&
        nodes == others.nodes &&
        captures == others.captures &&
        enpassant == others.enpassant &&
        castles == others.castles &&
        promotions == others.promotions &&
        checks == others.checks &&
        discoveryChecks == others.discoveryChecks &&
        doubleChecks == others.doubleChecks &&
        checkMates == others.checkMates;
}

void Perft::Diff(Perft& others){
    if(depth != others.depth){
        std::cout << "Invalid Depth " << std::endl;
    }
    if(nodes != others.nodes){
        std::cout << "No. of Nodes not matched" << std::endl;
    }
    if(captures != others.captures){
        std::cout << "No. of Captures not matched" << std::endl;
    }
    if(enpassant != others.enpassant){
        std::cout << "No. of En Passant not matched" << std::endl;
    }
    if(castles != others.castles){
        std::cout << "No. of Castles not matched" << std::endl;
    }
    if(promotions != others.promotions){
        std::cout << "No. of Promotions not matched" << std::endl;
    }
    if(checks != others.checks){
        std::cout << "No. of Checks not matched" << std::endl;
    }
    if(discoveryChecks != others.discoveryChecks){
        std::cout << "No. of Discovery Checks not matched" << std::endl;
    }
    if(doubleChecks != others.doubleChecks){
        std::cout << "No. of Double Checks not matched" << std::endl;
    }
    if(checkMates != others.checkMates){
        std::cout << "No. of Checkmates not matched" << std::endl;
    }
}

std::string Perft::toString(){
        return "Level " + std::to_string(depth) + ": " + std::to_string(nodes) + "\t"
        + " \tCaptures: " + std::to_string(captures) 
        + " \tE.p.: " + std::to_string(enpassant) 
        + " \tCastles: " + std::to_string(castles) 
        + " \tPromotions: " + std::to_string(promotions) 
        + " \tChecks: " + std::to_string(checks) 
        + " \tDiscovery Checks: " + std::to_string(discoveryChecks) 
        + " \tDouble Checks: " + std::to_string(doubleChecks) 
        + " \tCheckmates: " + std::to_string(checkMates);
}

PerftData::PerftData(){
    std::vector<Perft> position1;
    position1.push_back(Perft(1,20,0,0,0,0,0,0,0,0));
    position1.push_back(Perft(2,400,0,0,0,0,0,0,0,0));
    position1.push_back(Perft(3,8902,34,0,0,0,12,0,0,0));
    position1.push_back(Perft(4,197281,1576,0,0,0,469,0,0,8));
    position1.push_back(Perft(5,4865609,82719,258,0,0,27351,6,0,347));
    position1.push_back(Perft(6,119060324,2812008,5248,0,0,809099,329,46,10828));
    perftData.insert({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", position1});

    std::vector<Perft> position2;
    position2.push_back(Perft(1,48,8,0,2,0,0,0,0,0));
    position2.push_back(Perft(2,2039,351,1,91,0,3,0,0,0));
    position2.push_back(Perft(3,97862,17102,45,3162,0,993,0,0,1));
    position2.push_back(Perft(4,4085603,757163,1929,128013,15172,25523,42,6,43));
    position2.push_back(Perft(5,193690690,35043416,73365,4993637,8392,3309887,19883,2637,30171));
    //position2.push_back(Perft(6,8031647685,1558445089,3577504,184513607,56627920,92238050,568417,54948,360003));
    perftData.insert({"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -", position2});
}

PerftData::PerftData(std::string input){

}

Perft PerftData::Peek(std::string fen, int depth){
    return perftData[fen][depth];
}

bool PerftData::RunTest(std::string fen, std::vector<Perft> levels){
    for(int i = 0; i < levels.size(); i++){
        Perft perft = Peek(fen, i+1);
        std::cout << levels[i].toString() << std::endl;
        if(!levels[0].Equals(perft)){
            std::cout << perft.toString() << std::endl;
            std::cout << "Position: " << fen << " FAILED" << std::endl;
            levels[0].Diff(perft);
            return false;
        }
    }
    std::cout << "Position: " << fen << " PASSED" << std::endl;
    return true;
}
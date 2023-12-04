
#include "MagicUtil.h"

void MagicUtil::ListAllMagicBits(){
    MagicBits magicBits = MagicBits();
    std::cout << "Important Squares" << std::endl;
    //std::cout << magicBits.importantSquares.size() << std::endl;
    
    for(auto it=magicBits.importantBits.begin();it!=magicBits.importantBits.end();it++) {
        std::cout << it->first << "," <<it->second << std::endl;
        std::string s;
        s += std::to_string(it->first) + "," + std::to_string(it->second);
        Output(s);
        //BitUtil::bitboardToString(it->first);//Testing
    }
    
}

void MagicUtil::Output(std::string s){
    std::ofstream outfile;
    outfile.open("magic.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    outfile << s << std::endl;
    outfile.close();
}
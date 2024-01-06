
#include "MagicUtil.h"

void MagicUtil::ListAllMagicBits(){
    std::cout << "Start creating Magic bit boards" << std::endl;
    MagicBits magicBits;
    //std::cout << "Rook" << std::endl;
    //std::cout << magicBits.magicBishop[0].size() << std::endl;
    //for(int i = 0; i < 64; i++){
    //    std::cout << magicBits.magicRook[i].size() << std::endl;
    //}
    //
    //std::cout << "Bishop" << std::endl;
    //for(int i = 0; i < 64; i++){
    //    std::cout << magicBits.magicBishop[i].size() << std::endl;
    //}
    std::cout << "Done" << std::endl;
}

void MagicUtil::Output(std::string s){
    std::ofstream outfile;
    outfile.open("magic.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    outfile << s << std::endl;
    outfile.close();
}
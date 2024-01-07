
#include "MagicUtil.h"

MagicBits MagicUtil::magicBits = MagicBits();

void MagicUtil::ListAllMagicBits(){
}

void MagicUtil::Output(std::string s){
    std::ofstream outfile;
    outfile.open("magic.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    outfile << s << std::endl;
    outfile.close();
}
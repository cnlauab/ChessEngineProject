#include "MagicBits.h"

MagicBits::MagicBits(){
    for(SquareControl squareControl : ChessUtil::squareControlMap){
        std::cout << "MagicBits at " << ChessUtil::SquareToString(squareControl.origin);
        unsigned long long sidingBits = squareControl.queenControlBitboard;
        unsigned long long maxBits = ULLONG_MAX >> (64 - squareControl.allSlidingSquare.size());
        std::cout << " MaxBit = " << maxBits << std::endl;
        for(unsigned long long bits = 0ULL; bits <= maxBits; bits += 1ULL){
            //std::vector<short> important = {99,99,99,99,99,99,99,99};
            //unsigned long long emptyBits = 0ULL;
            unsigned long long important = 0ULL;

            std::vector<short> onBitIndex = BitUtil::getBitPositions(bits);
            std::vector<short> onSquares;
            for(short i : onBitIndex){
                onSquares.push_back(squareControl.allSlidingSquare[i]);
            }
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < squareControl.slidingSquare[i].size(); j++){
                    auto it = std::find(onSquares.begin(), onSquares.end(), squareControl.slidingSquare[i][j]);
                    if(it != onSquares.end()){
                        //important[i] = squareControl.slidingSquare[i][j];
                        important |= 1ULL << squareControl.slidingSquare[i][j];
                        break;
                    }else{
                        //emptyBits |= 1ULL << squareControl.slidingSquare[i][j];
                    }
                }
            }
            importantBits.insert({std::move(bits),std::move(important)});
            //emptySquaresBits.insert({indexBits,emptyBits});
        }
    }
}
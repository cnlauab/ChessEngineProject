#include "MagicBits.h"

MagicBits::MagicBits(){
    for(SquareControl squareControl : ChessUtil::squareControlMap){
        //std::cout << "MagicBits at " << ChessUtil::SquareToString(squareControl.origin) << std::endl;
        unsigned long long rookMask = squareControl.rookMagicBitMask;
        unsigned long long bishopMask = squareControl.bishopMagicBitMask;
        std::vector<short> rookIndex = BitUtil::getBitPositions(rookMask);
        std::vector<short> bishopIndex = BitUtil::getBitPositions(bishopMask);
        short rookMaskLength = rookIndex.size();
        short bishopMaskLength = bishopIndex.size();
        unsigned long long rookMax = (1ULL << rookMaskLength) - 1;
        unsigned long long bishopMax = (1ULL << bishopMaskLength) - 1;

        for(unsigned long long bits = 0ULL; bits <= bishopMax; bits += 1ULL){
            std::vector<short> onBits = BitUtil::getBitPositions(bits);
            std::vector<short> blockerBits;
            unsigned long long indexBits = 0ULL;
            unsigned long long magicBits = 0ULL;
            for(short onIndex : onBits){
                blockerBits.push_back(bishopIndex[onIndex]);
                indexBits |= 1ULL << bishopIndex[onIndex];
            }
            for(int i = 4; i < 8; i++){
                std::vector<short> targets = squareControl.slidingSquare[i];
                for(int j = 0; j < targets.size(); j++){
                    auto it = std::find(blockerBits.begin(), blockerBits.end(), targets[j]);
                    magicBits |= 1ULL << targets[j];
                    if(it != blockerBits.end()){
                        break;
                    }
                }
            }
            magicBishop[squareControl.origin].insert({indexBits, magicBits});
            
            //if(bits == bishopMax/10){
                //std::cout << "B Inserting: " << indexBits << " , " << magicBits << std::endl;
                //std::cout << "Mask: " << std::endl;
                //std::cout << BitUtil::bitboardToString(bishopMask) << std::endl;
                //std::cout << "Key: " << std::endl;
                //std::cout << BitUtil::bitboardToString(indexBits) << std::endl;
                //std::cout << "Magic: " << std::endl;
                //std::cout << BitUtil::bitboardToString(magicBits) << std::endl;
                //std::cout << "B Mask Length: " << std::endl;
                //std::cout << bishopMaskLength << std::endl;
            //}
        }

        for(unsigned long long bits = 0ULL; bits <= rookMax; bits += 1ULL){
            std::vector<short> onBits = BitUtil::getBitPositions(bits);
            std::vector<short> blockerBits;
            unsigned long long indexBits = 0ULL;
            unsigned long long magicBits = 0ULL;
            for(short onIndex : onBits){
                blockerBits.push_back(rookIndex[onIndex]);
                indexBits |= 1ULL << rookIndex[onIndex];
            }
            for(int i = 0; i < 4; i++){
                std::vector<short> targets = squareControl.slidingSquare[i];
                for(int j = 0; j < targets.size(); j++){
                    auto it = std::find(blockerBits.begin(), blockerBits.end(), targets[j]);
                    magicBits |= 1ULL << targets[j];
                    if(it != blockerBits.end()){
                        break;
                    }
                }
            }
            magicRook[squareControl.origin].insert({indexBits, magicBits});

            //if(bits == rookMax/10){
                //std::cout << "R Inserting: " << indexBits << " , " << magicBits << std::endl;
                //std::cout << "Mask: " << std::endl;
                //std::cout << BitUtil::bitboardToString(rookMask) << std::endl;
                //std::cout << "Key: " << std::endl;
                //std::cout << BitUtil::bitboardToString(indexBits) << std::endl;
                //std::cout << "Magic: " << std::endl;
                //std::cout << BitUtil::bitboardToString(magicBits) << std::endl;
                //std::cout << "R Mask Length: " << std::endl;
                //std::cout << rookMaskLength << std::endl;
            //}
        }
    }
}

unsigned long long MagicBits::GetRookMagic(short square, unsigned long long key){
    return magicRook[square][key];
}

unsigned long long MagicBits::GetBishopMagic(short square, unsigned long long key){
    return magicBishop[square][key];
}

unsigned long long MagicBits::GetQueenMagic(short square, unsigned long long rookKey, unsigned long long bishopKey){
    return magicRook[square][rookKey] | magicBishop[square][bishopKey];
}
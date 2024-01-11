#include "BitUtil.h"

std::unordered_map<char, int> BitUtil::pieceBitboardIndexMapping = {{'p',0}, {'q',1}, {'n',2}, {'b',3}, {'r',4}, {'k',5}};
char BitUtil::bitboardIndexPieceMapping[6] = {'p','q','n','b','r','k'};

std::unordered_map<unsigned long long, short> BitUtil::bitToSquareMap = {
    {1ULL<<0,0},
    {1ULL<<1,1},
    {1ULL<<2,2},
    {1ULL<<3,3},
    {1ULL<<4,4},
    {1ULL<<5,5},
    {1ULL<<6,6},
    {1ULL<<7,7},
    {1ULL<<8,8},
    {1ULL<<9,9},
    {1ULL<<10,10},
    {1ULL<<11,11},
    {1ULL<<12,12},
    {1ULL<<13,13},
    {1ULL<<14,14},
    {1ULL<<15,15},
    {1ULL<<16,16},
    {1ULL<<17,17},
    {1ULL<<18,18},
    {1ULL<<19,19},
    {1ULL<<20,20},
    {1ULL<<21,21},
    {1ULL<<22,22},
    {1ULL<<23,23},
    {1ULL<<24,24},
    {1ULL<<25,25},
    {1ULL<<26,26},
    {1ULL<<27,27},
    {1ULL<<28,28},
    {1ULL<<29,29},
    {1ULL<<30,30},
    {1ULL<<31,31},
    {1ULL<<32,32},
    {1ULL<<33,33},
    {1ULL<<34,34},
    {1ULL<<35,35},
    {1ULL<<36,36},
    {1ULL<<37,37},
    {1ULL<<38,38},
    {1ULL<<39,39},
    {1ULL<<40,40},
    {1ULL<<41,41},
    {1ULL<<42,42},
    {1ULL<<43,43},
    {1ULL<<44,44},
    {1ULL<<45,45},
    {1ULL<<46,46},
    {1ULL<<47,47},
    {1ULL<<48,48},
    {1ULL<<49,49},
    {1ULL<<50,50},
    {1ULL<<51,51},
    {1ULL<<52,52},
    {1ULL<<53,53},
    {1ULL<<54,54},
    {1ULL<<55,55},
    {1ULL<<56,56},
    {1ULL<<57,57},
    {1ULL<<58,58},
    {1ULL<<59,59},
    {1ULL<<60,60},
    {1ULL<<61,61},
    {1ULL<<62,62},
    {1ULL<<63,63}
};
std::unordered_map<char, unsigned long long> BitUtil::castleBlockingBits = {{'K',112ULL},{'Q',28ULL},{'k',8070450532247928832ULL},{'q',2017612633061982208ULL}};
std::unordered_map<char, unsigned long long> BitUtil::friendlyCastleBlockingBits = {{'K',96ULL},{'Q',14ULL},{'k',1729382256910270464ULL},{'q',1008806316530991104ULL}};


std::string BitUtil::bitboardToString(unsigned long long bitboard){
    //std::cout << "Printing bitboard (Value: " << bitboard << ")" << std::endl;
    //i;
    short index = 0;
    std::string result = "";
    std::string row = "";
    unsigned long long number = 1ULL;
    for(int i = 1; i <= 64; i++){
        if((bitboard & number) != 0){
            row = row + "[1]";
        }else{
            row = row + "[0]";
        }
        if(i % 8 == 0){
            result = row + std::to_string(i/8) + "\n" + result;
            row = "";
        }
        number = number << 1;
    }
    result = result + " a  b  c  d  e  f  g  h ";
    return result;
} 

std::vector<short> BitUtil::getBitPositions(unsigned long long bitboard){
    std::vector<short> result;
    unsigned long long tmpBitboard = bitboard;

    while(tmpBitboard > 0ULL){
        int leadingZeros = __builtin_clzll(tmpBitboard);
        short leftMostIndex = 63 - leadingZeros;
        result.push_back(leftMostIndex);
        tmpBitboard &= ~(1ULL << leftMostIndex);
    }
    return result;
}

short BitUtil::getNumberOnBits(unsigned long long bitboard){
    short result;
    unsigned long long tmpBitboard = bitboard;

    while(tmpBitboard > 0ULL){
        int leadingZeros = __builtin_clzll(tmpBitboard);
        short leftMostIndex = 63 - leadingZeros;
        result+=1;
        tmpBitboard &= ~(1ULL << leftMostIndex);
    }
    return result;
}

unsigned long long BitUtil::knightControlBits(unsigned long long knightbits){
    unsigned long long result = 0ULL;
    unsigned long long knightSquare1 = knightbits & ~(hFile | seventhRank | eighthRank);
    unsigned long long knightSquare2 = knightbits & ~(hFile | gFile | eighthRank);
    unsigned long long knightSquare3 = knightbits & ~(hFile | gFile | firstRank);
    unsigned long long knightSquare4 = knightbits & ~(hFile | firstRank | secondRank);
    unsigned long long knightSquare5 = knightbits & ~(aFile | firstRank | secondRank);
    unsigned long long knightSquare6 = knightbits & ~(aFile | bFile | firstRank);
    unsigned long long knightSquare7 = knightbits & ~(aFile | bFile | eighthRank);
    unsigned long long knightSquare8 = knightbits & ~(aFile | seventhRank | eighthRank);
    if(knightSquare1 > 0ULL){
        result |= knightSquare1 << 17;
    }
    if(knightSquare2 > 0ULL){
        result |= knightSquare2 << 10;
    }
    if(knightSquare3 > 0ULL){
        result |= knightSquare3 >> 6;
    }
    if(knightSquare4 > 0ULL){
        result |= knightSquare4 >> 15;
    }
    if(knightSquare5 > 0ULL){
        result |= knightSquare5 >> 17;
    }
    if(knightSquare6 > 0ULL){
        result |= knightSquare6 >> 10;
    }
    if(knightSquare7 > 0ULL){
        result |= knightSquare7 << 6;
    }
    if(knightSquare8 > 0ULL){
        result |= knightSquare8 << 15;
    }
    return result;
}

unsigned long long BitUtil::pawnControlBits(unsigned long long pawnbits, bool white){
    if(white){
        unsigned long long pawnsMovingRight = pawnbits & ~(hFile | eighthRank);
        unsigned long long pawnsMovingLeft = pawnbits & ~(aFile | eighthRank);
        return (pawnsMovingRight << 9) | (pawnsMovingLeft << 7);
    }else{
        unsigned long long pawnsMovingRight = pawnbits & ~(hFile | firstRank);
        unsigned long long pawnsMovingLeft = pawnbits & ~(aFile | firstRank);
        return (pawnsMovingRight >> 7) | (pawnsMovingLeft >> 9);
    }
}

unsigned long long BitUtil::kingControlBits(unsigned long long kingbit){
    unsigned long long result = 0ULL;
    unsigned long long kingDown = kingbit & ~firstRank;
    unsigned long long kingUp = kingbit & ~eighthRank;
    unsigned long long kingLeft = kingbit & ~aFile;
    unsigned long long kingRight = kingbit & ~hFile;
    unsigned long long kingDownLeft = kingbit & ~aFile & ~firstRank;
    unsigned long long kingDownRight = kingbit & ~hFile & ~firstRank;
    unsigned long long kingUpLeft = kingbit & ~aFile & ~eighthRank;
    unsigned long long kingUpRight = kingbit & ~hFile & ~eighthRank;
    if(kingDown > 0ULL){
        result |= kingDown >> 8;
    }
    if(kingUp > 0ULL){
        result |= kingUp << 8;
    }
    if(kingLeft > 0ULL){
        result |= kingLeft >> 1;
    }
    if(kingRight > 0ULL){
        result |= kingRight << 1;
    }
    if(kingDownLeft > 0ULL){
        result |= kingDownLeft >> 9;
    }
    if(kingDownRight > 0ULL){
        result |= kingDownRight >> 7;
    }
    if(kingUpLeft > 0ULL){
        result |= kingUpLeft << 7;
    }
    if(kingUpRight > 0ULL){
        result |= kingUpRight << 9;
    }
    return result;
}

unsigned long long BitUtil::GetFileBit(short file){
    if(file > 7 || file < 0) return 0ULL;
    return aFile << file;
}

unsigned long long BitUtil::GetRankBit(short rank){
    if(rank > 7 || rank < 0) return 0ULL;
    return firstRank << rank;
}

unsigned long long BitUtil::GetMagicKey(unsigned long long allPieces, short square, bool diagonal){
    if(diagonal){
        return allPieces & ChessUtil::squareControlMap[square].bishopMagicBitMask;
    }else{
        return allPieces & ChessUtil::squareControlMap[square].rookMagicBitMask;
    }

}

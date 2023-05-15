#include "ChessUtil.h"
std::unordered_map<int, char> ChessUtil::pieceMapping = {
        {-32,'n'},
        {-31,'n'},
        {-30,'n'},
        {-29,'n'},
        {-28,'n'},
        {-27,'n'},
        {-26,'n'},
        {-25,'n'},
        {-24,'r'},
        {-23,'r'},
        {-22,'r'},
        {-21,'r'},
        {-20,'r'},
        {-19,'r'},
        {-18,'r'},
        {-17,'r'},
        {-16,'b'},
        {-15,'b'},
        {-14,'b'},
        {-13,'b'},
        {-12,'b'},
        {-11,'b'},
        {-10,'b'},
        {-9,'b'},
        {-8,'q'},
        {-7,'q'},
        {-6,'q'},
        {-5,'q'},
        {-4,'q'},
        {-3,'q'},
        {-2,'q'},
        {-1,'q'},
        {0,'r'},
        {1,'n'},
        {2,'b'},
        {3,'q'},
        {4,'k'},
        {5,'b'},
        {6,'n'},
        {7,'r'},
        {8,'p'},
        {9,'p'},
        {10,'p'},
        {11,'p'},
        {12,'p'},
        {13,'p'},
        {14,'p'},
        {15,'p'},
        {48,'P'},
        {49,'P'},
        {50,'P'},
        {51,'P'},
        {52,'P'},
        {53,'P'},
        {54,'P'},
        {55,'P'},
        {56,'R'},
        {57,'N'},
        {58,'B'},
        {59,'Q'},
        {60,'K'},
        {61,'B'},
        {62,'N'},
        {63,'R'},
        {64,'Q'},
        {65,'Q'},
        {66,'Q'},
        {67,'Q'},
        {68,'Q'},
        {69,'Q'},
        {70,'Q'},
        {71,'Q'},
        {72,'B'},
        {73,'B'},
        {74,'B'},
        {75,'B'},
        {76,'B'},
        {77,'B'},
        {78,'B'},
        {79,'B'},
        {80,'R'},
        {81,'R'},
        {82,'R'},
        {83,'R'},
        {84,'R'},
        {85,'R'},
        {86,'R'},
        {87,'R'},
        {88,'N'},
        {89,'N'},
        {90,'N'},
        {91,'N'},
        {92,'N'},
        {93,'N'},
        {94,'N'},
        {95,'N'},
        {99,' '}
};

char ChessUtil::file[8] = { 'a','b','c','d','e','f','g','h' };
char ChessUtil::rank[8] = { '1','2','3','4','5','6','7','8' };
int ChessUtil::offsets[8] = { -1,1,-8,8,-9,-7,7,9 };

std::unordered_map <std::string, int> ChessUtil::squareToIndexMapping = {
    {"a1", 0},
    {"b1", 1},
    {"c1", 2},
    {"d1", 3},
    {"e1", 4},
    {"f1", 5},
    {"g1", 6},
    {"h1", 7},
    {"a2", 8},
    {"b2", 9},
    {"c2", 10},
    {"d2", 11},
    {"e2", 12},
    {"f2", 13},
    {"g2", 14},
    {"h2", 15},
    {"a3", 16},
    {"b3", 17},
    {"c3", 18},
    {"d3", 19},
    {"e3", 20},
    {"f3", 21},
    {"g3", 22},
    {"h3", 23},
    {"a4", 24},
    {"b4", 25},
    {"c4", 26},
    {"d4", 27},
    {"e4", 28},
    {"f4", 29},
    {"g4", 30},
    {"h4", 31},
    {"a5", 32},
    {"b5", 33},
    {"c5", 34},
    {"d5", 35},
    {"e5", 36},
    {"f5", 37},
    {"g5", 38},
    {"h5", 39},
    {"a6", 40},
    {"b6", 41},
    {"c6", 42},
    {"d6", 43},
    {"e6", 44},
    {"f6", 45},
    {"g6", 46},
    {"h6", 47},
    {"a7", 48},
    {"b7", 49},
    {"c7", 50},
    {"d7", 51},
    {"e7", 52},
    {"f7", 53},
    {"g7", 54},
    {"h7", 55},
    {"a8", 56},
    {"b8", 57},
    {"c8", 58},
    {"d8", 59},
    {"e8", 60},
    {"f8", 61},
    {"g8", 62},
    {"h8", 63}
};

char ChessUtil::GetPieceType(int piece) {
    return pieceMapping[piece];
};

int ChessUtil::GetRank(int square)
{
    return square / 8;
}

int ChessUtil::GetFile(int square)
{
    return square % 8;
}

char ChessUtil::GetRankChar(int square)
{
    return rank[GetRank(square)];
}

char ChessUtil::GetFileChar(int square)
{
    return file[GetFile(square)];
}

std::string ChessUtil::SquareToString(int square)
{
    std::string result;
    result.push_back(GetFileChar(square));
    result.push_back(GetRankChar(square));
    return result;
}

int ChessUtil::StringToSquare(std::string squareString)
{
    if(squareString.length() > 2) return 99;
    return squareToIndexMapping[squareString];
}

int ChessUtil::GetRankFromChar(char rank) {
    for (int i = 0; i < 8; ++i) {
        if (ChessUtil::rank[i] == rank) return i;
    }
    return 99;
}

int ChessUtil::GetFileFromChar(char file) {
    for (int i = 0; i < 8; ++i) {
        if (ChessUtil::file[i] == file) return i;
    }
    return 99;
}

bool ChessUtil::IsWhite(int piece)
{
    return piece < 32;
}

bool ChessUtil::IsPawn(int piece)
{
    return (piece >= 8 && piece <= 15) || (piece >= 8 && piece <= 15);
}

bool ChessUtil::IsKing(int piece)
{
    return piece == 4 || piece == 60;
}

bool ChessUtil::IsRook(int piece)
{
    return piece == 0 || piece == 7 || piece == 56 || piece == 63 || (piece >= -24 && piece <= -17) || (piece >= 80 && piece <= 87);
}

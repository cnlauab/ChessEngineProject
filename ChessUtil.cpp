#include "ChessUtil.h"
std::unordered_map<int, char> ChessUtil::pieceMapping = {
        {-32,'N'},
        {-31,'N'},
        {-30,'N'},
        {-29,'N'},
        {-28,'N'},
        {-27,'N'},
        {-26,'N'},
        {-25,'N'},
        {-24,'R'},
        {-23,'R'},
        {-22,'R'},
        {-21,'R'},
        {-20,'R'},
        {-19,'R'},
        {-18,'R'},
        {-17,'R'},
        {-16,'B'},
        {-15,'B'},
        {-14,'B'},
        {-13,'B'},
        {-12,'B'},
        {-11,'B'},
        {-10,'B'},
        {-9,'B'},
        {-8,'Q'},
        {-7,'Q'},
        {-6,'Q'},
        {-5,'Q'},
        {-4,'Q'},
        {-3,'Q'},
        {-2,'Q'},
        {-1,'Q'},
        {0,'R'},
        {1,'N'},
        {2,'B'},
        {3,'Q'},
        {4,'K'},
        {5,'B'},
        {6,'N'},
        {7,'R'},
        {8,'P'},
        {9,'P'},
        {10,'P'},
        {11,'P'},
        {12,'P'},
        {13,'P'},
        {14,'P'},
        {15,'P'},
        {48,'p'},
        {49,'p'},
        {50,'p'},
        {51,'p'},
        {52,'p'},
        {53,'p'},
        {54,'p'},
        {55,'p'},
        {56,'r'},
        {57,'n'},
        {58,'b'},
        {59,'q'},
        {60,'k'},
        {61,'b'},
        {62,'n'},
        {63,'r'},
        {64,'q'},
        {65,'q'},
        {66,'q'},
        {67,'q'},
        {68,'q'},
        {69,'q'},
        {70,'q'},
        {71,'q'},
        {72,'b'},
        {73,'b'},
        {74,'b'},
        {75,'b'},
        {76,'b'},
        {77,'b'},
        {78,'b'},
        {79,'b'},
        {80,'r'},
        {81,'r'},
        {82,'r'},
        {83,'r'},
        {84,'r'},
        {85,'r'},
        {86,'r'},
        {87,'r'},
        {88,'n'},
        {89,'n'},
        {90,'n'},
        {91,'n'},
        {92,'n'},
        {93,'n'},
        {94,'n'},
        {95,'n'},
        {99,' '}
};

std::unordered_map<int, int> ChessUtil::pieceValueMapping = {
        {-32,3},
        {-31,3},
        {-30,3},
        {-29,3},
        {-28,3},
        {-27,3},
        {-26,3},
        {-25,3},
        {-24,5},
        {-23,5},
        {-22,5},
        {-21,5},
        {-20,5},
        {-19,5},
        {-18,5},
        {-17,5},
        {-16,3},
        {-15,3},
        {-14,3},
        {-13,3},
        {-12,3},
        {-11,3},
        {-10,3},
        {-9,3},
        {-8,9},
        {-7,9},
        {-6,9},
        {-5,9},
        {-4,9},
        {-3,9},
        {-2,9},
        {-1,9},
        {0,5},
        {1,3},
        {2,3},
        {3,9},
        {4,99},
        {5,3},
        {6,3},
        {7,5},
        {8,1},
        {9,1},
        {10,1},
        {11,1},
        {12,1},
        {13,1},
        {14,1},
        {15,1},
        {48,-1},
        {49,-1},
        {50,-1},
        {51,-1},
        {52,-1},
        {53,-1},
        {54,-1},
        {55,-1},
        {56,-5},
        {57,-3},
        {58,-3},
        {59,-9},
        {60,-99},
        {61,-3},
        {62,-3},
        {63,-5},
        {64,-9},
        {65,-9},
        {66,-9},
        {67,-9},
        {68,-9},
        {69,-9},
        {70,-9},
        {71,-9},
        {72,-3},
        {73,-3},
        {74,-3},
        {75,-3},
        {76,-3},
        {77,-3},
        {78,-3},
        {79,-3},
        {80,-5},
        {81,-5},
        {82,-5},
        {83,-5},
        {84,-5},
        {85,-5},
        {86,-5},
        {87,-5},
        {88,-3},
        {89,-3},
        {90,-3},
        {91,-3},
        {92,-3},
        {93,-3},
        {94,-3},
        {95,-3},
        {99,0}
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

SquareControl ChessUtil::squareControlMap[64] = {
    SquareControl(0),
    SquareControl(1),
    SquareControl(2),
    SquareControl(3),
    SquareControl(4),
    SquareControl(5),
    SquareControl(6),
    SquareControl(7),
    SquareControl(8),
    SquareControl(9),
    SquareControl(10),
    SquareControl(11),
    SquareControl(12),
    SquareControl(13),
    SquareControl(14),
    SquareControl(15),
    SquareControl(16),
    SquareControl(17),
    SquareControl(18),
    SquareControl(19),
    SquareControl(20),
    SquareControl(21),
    SquareControl(22),
    SquareControl(23),
    SquareControl(24),
    SquareControl(25),
    SquareControl(26),
    SquareControl(27),
    SquareControl(28),
    SquareControl(29),
    SquareControl(30),
    SquareControl(31),
    SquareControl(32),
    SquareControl(33),
    SquareControl(34),
    SquareControl(35),
    SquareControl(36),
    SquareControl(37),
    SquareControl(38),
    SquareControl(39),
    SquareControl(40),
    SquareControl(41),
    SquareControl(42),
    SquareControl(43),
    SquareControl(44),
    SquareControl(45),
    SquareControl(46),
    SquareControl(47),
    SquareControl(48),
    SquareControl(49),
    SquareControl(50),
    SquareControl(51),
    SquareControl(52),
    SquareControl(53),
    SquareControl(54),
    SquareControl(55),
    SquareControl(56),
    SquareControl(57),
    SquareControl(58),
    SquareControl(59),
    SquareControl(60),
    SquareControl(61),
    SquareControl(62),
    SquareControl(63)
};

char ChessUtil::GetPieceType(int piece) {
    return pieceMapping[piece];
};

int ChessUtil::GetRank(int square)
{
    return SquareControl::GetRank(square);
}

int ChessUtil::GetFile(int square)
{
    return SquareControl::GetFile(square);
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

bool ChessUtil::SquareOutbound(int startingSquare, int targetSquare, int offsetType) {
	return SquareControl::SquareOutbound(startingSquare, targetSquare, offsetType);
}

bool ChessUtil::IsEmpty(int piece)
{
    return piece == 99;
}

bool ChessUtil::IsWhite(int piece)
{
    return piece < 32;
}

bool ChessUtil::IsPawn(int piece)
{
    return (piece >= 8 && piece <= 15) || (piece >= 48 && piece <= 55);
}

bool ChessUtil::IsQueen(int piece)
{
    return piece == 3 || piece == 59 || (piece >= -8 && piece <= -1) || (piece >= 64 && piece <= 71);
}

bool ChessUtil::IsBishop(int piece)
{
    return piece == 2 || piece == 5 || piece == 58 || piece == 61 || (piece >= -16 && piece <= -9) || (piece >= 72 && piece <= 79);
}

bool ChessUtil::IsKnight(int piece)
{
    return piece == 1 || piece == 6 || piece == 57 || piece == 62 || (piece >= -32 && piece <= -25) || (piece >= 88 && piece <= 95);
}

bool ChessUtil::IsKing(int piece)
{
    return piece == 4 || piece == 60;
}

bool ChessUtil::IsRook(int piece)
{
    return piece == 0 || piece == 7 || piece == 56 || piece == 63 || (piece >= -24 && piece <= -17) || (piece >= 80 && piece <= 87);
}


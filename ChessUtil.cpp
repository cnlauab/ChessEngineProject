#include "ChessUtil.h"
std::unordered_map<short, char> ChessUtil::pieceMapping = {
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
std::unordered_map<short, short> ChessUtil::pieceScoreMapping = {
        {-32,30},
        {-31,30},
        {-30,30},
        {-29,30},
        {-28,30},
        {-27,30},
        {-26,30},
        {-25,30},
        {-24,50},
        {-23,50},
        {-22,50},
        {-21,50},
        {-20,50},
        {-19,50},
        {-18,50},
        {-17,50},
        {-16,30},
        {-15,30},
        {-14,30},
        {-13,30},
        {-12,30},
        {-11,30},
        {-10,30},
        {-9,30},
        {-8,90},
        {-7,90},
        {-6,90},
        {-5,90},
        {-4,90},
        {-3,90},
        {-2,90},
        {-1,90},
        {0,50},
        {1,30},
        {2,30},
        {3,90},
        {4,0},
        {5,30},
        {6,30},
        {7,50},
        {8,10},
        {9,10},
        {10,10},
        {11,10},
        {12,10},
        {13,10},
        {14,10},
        {15,10},
        {48,10},
        {49,10},
        {50,10},
        {51,10},
        {52,10},
        {53,10},
        {54,10},
        {55,10},
        {56,50},
        {57,30},
        {58,30},
        {59,90},
        {60,0},
        {61,30},
        {62,30},
        {63,50},
        {64,90},
        {65,90},
        {66,90},
        {67,90},
        {68,90},
        {69,90},
        {70,90},
        {71,90},
        {72,30},
        {73,30},
        {74,30},
        {75,30},
        {76,30},
        {77,30},
        {78,30},
        {79,30},
        {80,50},
        {81,50},
        {82,50},
        {83,50},
        {84,50},
        {85,50},
        {86,50},
        {87,50},
        {88,90},
        {89,90},
        {90,90},
        {91,90},
        {92,90},
        {93,90},
        {94,90},
        {95,90},
        {99,0}
};
short ChessUtil::pieceTypeScoreMapping[6] = {10, 90, 30, 30, 50, 1000};
std::unordered_map<char, short> ChessUtil::castlingTargetMapping = {{'K',6},{'Q',2},{'k',62},{'q',58}}; 

char ChessUtil::file[8] = { 'a','b','c','d','e','f','g','h' };
char ChessUtil::rank[8] = { '1','2','3','4','5','6','7','8' };
short ChessUtil::offsets[8] = { -1,1,-8,8,-9,-7,7,9 };
short ChessUtil::midGameScoreMap[64] = {
		1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,1,
		1,2,3,3,3,3,2,1,
		1,2,3,5,5,3,2,1,
		1,2,3,5,5,3,2,1,
		1,2,3,3,3,3,2,1,
		1,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,
	};
short ChessUtil::endGameScoreMap[64] = {
        5,5,5,5,5,5,5,5,
        3,3,3,3,3,3,3,3,
        1,1,1,2,2,1,1,1,
        1,1,2,2,2,2,1,1,
        1,1,2,2,2,2,1,1,
        1,1,1,2,2,1,1,1,
        3,3,3,3,3,3,3,3,
        5,5,5,5,5,5,5,5,
    };
short ChessUtil::checkScore = 100;

std::unordered_map <std::string, short> ChessUtil::squareToIndexMapping = {
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
std::unordered_map<char, unsigned short> ChessUtil::promotionTypeMap = {{'Q',0},{'N',1},{'R',2},{'B',3},{' ',0}};

char ChessUtil::GetPieceType(short piece) {
    return pieceMapping[piece];
};

short ChessUtil::GetRank(short square)
{
    return squareControlMap[square].rank;
}

short ChessUtil::GetFile(short square)
{
    return squareControlMap[square].file;
}

char ChessUtil::GetRankChar(short square)
{
    return rank[GetRank(square)];
}

char ChessUtil::GetFileChar(short square)
{
    return file[GetFile(square)];
}

std::string ChessUtil::SquareToString(short square)
{
    std::string result;
    result.push_back(GetFileChar(square));
    result.push_back(GetRankChar(square));
    return result;
}

short ChessUtil::StringToSquare(std::string squareString)
{
    if(squareString.length() > 2) return 99;
    return squareToIndexMapping[squareString];
}

short ChessUtil::GetRankFromChar(char rank) {
    for (int i = 0; i < 8; ++i) {
        if (ChessUtil::rank[i] == rank) return i;
    }
    return 99;
}

short ChessUtil::GetFileFromChar(char file) {
    for (int i = 0; i < 8; ++i) {
        if (ChessUtil::file[i] == file) return i;
    }
    return 99;
}

short ChessUtil::GetSquareFromFileRank(short file, short rank){
    return rank * 8 + file;
}

bool ChessUtil::SquareOutbound(short startingSquare, short targetSquare, short offsetType) {
	return SquareControl::SquareOutbound(startingSquare, targetSquare, offsetType);
}

bool ChessUtil::IsEmpty(short piece)
{
    return piece == 99;
}

bool ChessUtil::IsWhite(short piece)
{
    return piece < 32;
}

bool ChessUtil::IsPawn(short piece)
{
    return (piece >= 8 && piece <= 15) || (piece >= 48 && piece <= 55);
}

bool ChessUtil::IsQueen(short piece)
{
    return piece == 3 || piece == 59 || (piece >= -8 && piece <= -1) || (piece >= 64 && piece <= 71);
}

bool ChessUtil::IsBishop(short piece)
{
    return piece == 2 || piece == 5 || piece == 58 || piece == 61 || (piece >= -16 && piece <= -9) || (piece >= 72 && piece <= 79);
}

bool ChessUtil::IsKnight(short piece)
{
    return piece == 1 || piece == 6 || piece == 57 || piece == 62 || (piece >= -32 && piece <= -25) || (piece >= 88 && piece <= 95);
}

bool ChessUtil::IsKing(short piece)
{
    return piece == 4 || piece == 60;
}

bool ChessUtil::IsRook(short piece)
{
    return piece == 0 || piece == 7 || piece == 56 || piece == 63 || (piece >= -24 && piece <= -17) || (piece >= 80 && piece <= 87);
}

bool ChessUtil::IsLightSquare(short square){
    return square == 1 || square == 3 || square == 5 || square == 7 || square == 8 || square == 10 || square == 12 || square == 14 || square == 17 || square == 19 || square == 21 || square == 23 || square == 24 || square == 26 || square == 28 || square == 30 || square == 33 || square == 35 || square == 37 || square == 39 || square == 40 || square == 42 || square == 44 || square == 46 || square == 49 || square == 51 || square == 53 || square == 55 || square == 56 || square == 58 || square == 60 || square == 62;
}

unsigned short ChessUtil::SimpleMove(short from, short to, bool capture, char promotionType){
    //if(capture) std::cout << ChessUtil::SquareToString(from) << "," << ChessUtil::SquareToString(to) << std::endl;
    return (unsigned short)from | ((unsigned short)to << 6) | (ChessUtil::promotionTypeMap[promotionType] << 12) | ((unsigned short)capture << 14) | ((unsigned short)(promotionType != ' ') << 15);
}

short ChessUtil::GetFrom(unsigned short move){
    return move & 63;
}

short ChessUtil::GetTo(unsigned short move){
    return (move >> 6) & 63;
}

char ChessUtil::GetPromotionType(unsigned short move){
    unsigned short index = (move >> 12) & 3;
    switch(index){
        case 0://0b0000
            return 'Q';
        case 1://0b0001
            return 'N';
        case 2://0b0010
            return 'R';
        case 3://0b0011
            return 'B';
        default:
            return ' ';
    }
}

bool ChessUtil::GetIsCapture(unsigned short move){
    return (move >> 14) & 1;
}

bool ChessUtil::GetIsPromotion(unsigned short move){
    return (move >> 15) & 1;
}

std::string ChessUtil::SimpleMoveToString(unsigned short move){
    bool promotion = GetIsPromotion(move);
    bool capture = GetIsCapture(move);
    std::string result = ChessUtil::SquareToString(GetFrom(move));
    //if(capture) result += 'x';
    result += ChessUtil::SquareToString(GetTo(move));
    if(promotion) result += tolower(GetPromotionType(move));
    return result;
    //return ChessUtil::SquareToString(GetFrom(move)) + ChessUtil::SquareToString(GetTo(move)) + '=' + GetPromotionType(move);
}

unsigned short ChessUtil::UCIToMove(std::string uci){
	short from  = ChessUtil::GetSquareFromFileRank(ChessUtil::GetFileFromChar(uci[0]),ChessUtil::GetRankFromChar(uci[1]));
	short to = ChessUtil::GetSquareFromFileRank(ChessUtil::GetFileFromChar(uci[2]),ChessUtil::GetRankFromChar(uci[3]));
	
    if(uci.length() > 4 && uci[4] != ' ') {
        char promotionType = (char)toupper(uci[4]);
        return ChessUtil::SimpleMove(from, to, promotionType);
    }else{
        return ChessUtil::SimpleMove(from, to);
    }
}

void ChessUtil::PrintMoveList(std::vector<unsigned short>& moves){
    if(moves.size() == 0) std::cout << "Empty Move List" << std::endl;
    for(int i = 0; i < moves.size(); i++){
        std::cout << SimpleMoveToString(moves[i]) << std::endl;
    }
}
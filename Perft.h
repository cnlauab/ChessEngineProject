#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Perft{
    public:
        int depth = 0;

        int nodes = 0;
        int captures = 0;
        int enpassant = 0;
        int castles = 0;
        int promotions = 0;
        int checks = 0;
        int discoveryChecks = 0;
        int doubleChecks = 0;
        int checkMates = 0;

        Perft(std::string line);
        Perft(int depth);
        Perft(int depth, int nodes, int captures, int enpassant, int castles, int promotions, int checks, int discoveryChecks, int doubleChecks, int checkMates);

        Perft(Perft& other);
        Perft(Perft&& other);
        Perft& operator=(Perft&& other);

        void Add(bool captures, bool enpassant, bool castles, bool promotions, bool checks, bool discoveryChecks, bool doubleChecks, bool checkMates);
        void Add(Perft& others);
        bool Equals(Perft& others);
        void Diff(Perft& others);
        std::string toString();
};

class PerftData{
    public:
        std::unordered_map<std::string, std::vector<Perft>> perftData;

        PerftData();
        PerftData(std::string input);
        Perft Peek(std::string fen, int depth);
        bool RunTest(std::string fen, std::vector<Perft> levels);
};
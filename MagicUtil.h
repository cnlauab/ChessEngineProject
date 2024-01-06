#pragma once

#include "MagicBits.h"
#include <iostream>
#include <fstream>

class MagicUtil{
    public :
        static MagicBits magicBits;

        static void ListAllMagicBits();
        static void Output(std::string s);

};
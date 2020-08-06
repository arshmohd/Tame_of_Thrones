#ifndef GOLDEN_CROWN_H
#define GOLDEN_CROWN_H

#include <iostream>
#include <map>          // Map/Dictionary, extract
#include <string>       // String datatype and its functions.
#include <vector>       // Vector datatype for list of allies.
#include <iterator>     // For iterator.
#include <cctype>       // For Character based functions
#include <algorithm>    // For binary_search, transform
#include <sstream>      // std::istringstream
#include <fstream>      // To work with files.   

class Game
{   
    static const int MINALLIES = 3;
    static int counter;

    const int DECAP = 65;
    const int ALPH = 26;
    const std::string LAND_EMBLEM = "AADNP";
    const std::string WATER_EMBLEM = "COOPSTU";
    const std::string ICE_EMBLEM = "AHMMMOT";
    const std::string AIR_EMBLEM = "LOW";
    const std::string FIRE_EMBLEM = "ADGNOR";

    const std::map<std::string, std::pair<std::string, int>> southeros {
        {"LAND", {LAND_EMBLEM, LAND_EMBLEM.size()}},
        {"WATER", {WATER_EMBLEM, WATER_EMBLEM.size()}},
        {"ICE", {ICE_EMBLEM, ICE_EMBLEM.size()}},
        {"AIR", {AIR_EMBLEM, AIR_EMBLEM.size()}},
        {"FIRE", {FIRE_EMBLEM, FIRE_EMBLEM.size()}}
    };

    std::map<std::string, std::string> decrypted;
    std::vector<std::string> allies;
    int totalAllies = 0;                                     // Ally counter.     

    public:

        int get_totalAllies();

        bool check_totalAllies();

        std::vector<std::string> get_allies();

        Game(std::map<std::string, std::string> messages);

        ~Game();

        void encoder();

        void decoder(std::map<std::string, std::string> encrypted);
};

std::ostream& operator << (std::ostream& output, std::map<std::string, std::string> message);

std::ostream& operator << (std::ostream& output, std::vector<std::string> vecs);

void mess_cleaner(std::map<std::string, std::string> &mess);

void removeC(std::string &legacy, char c);

std::map<std::string, std::string> file2map(std::ifstream& inFile);

unsigned int modulo(int value, unsigned int m);

#endif
//
// Created by wiley on 3/4/2025.
//

#pragma once

#include <string>
#include <fstream>

class Game
{
public:
    std::string m_name;
    Game(const std::string& name) : m_name(name) {}
    void save(std::ofstream& outf);
    static void load(std::ifstream& inf, Game*& outGame);

    std::string toString()
    {
        return m_name;
    }
};

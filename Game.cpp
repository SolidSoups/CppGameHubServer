//
// Created by wiley on 3/4/2025.
//

#include "Game.h"

void Game::save(std::ofstream& outf)
{
    size_t nameSize = m_name.size();
    outf.write(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
    outf.write(m_name.c_str(), nameSize);
}
void Game::load(std::ifstream& inf, Game*& outGame) {
    size_t nameSize;
    inf.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
    std::string newName(nameSize, '\0');
    inf.read(&newName[0], nameSize);

    outGame = new Game(newName);
}

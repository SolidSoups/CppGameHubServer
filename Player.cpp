//
// Created by wiley on 3/8/2025.
//

#include "Player.h"

bool Player::login(const std::string& password)
{
	if (m_password == password)
		return true;
	return false;
}

void Player::addGame(const Game& newGame)
{
	std::string gameString = newGame.m_name;
	m_ownedGames.push_back(gameString);
}

std::string Player::getEmail()
{
	return m_email;
}

void Player::save(std::ofstream& outf)
{
    // write email
    size_t emailSize = m_email.size();
    outf.write(reinterpret_cast<char*>(&emailSize), sizeof(size_t));
    outf.write(m_email.c_str(), emailSize);

    // write password *super secret style*
    size_t passSize = m_password.size();
    outf.write(reinterpret_cast<char*>(&passSize), sizeof(size_t));
    outf.write(m_password.c_str(), passSize);

	// write owned games
	size_t gamesSize = m_ownedGames.size();
	outf.write(reinterpret_cast<char*>(&gamesSize), sizeof(size_t));
	for (int i=0; i<gamesSize; i++)
	{
		// write game
		size_t gameSize = m_ownedGames[i].size();
		outf.write(reinterpret_cast<char*>(&gameSize), sizeof(size_t));
		outf.write(m_ownedGames[i].c_str(), gameSize);
	}
}

const std::vector<std::string>& Player::getGames()
{
	return m_ownedGames;
}

void Player::load(std::ifstream& inf, Player*& outPlayer)
{
    // read email
    size_t emailSize;
    inf.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
    std::string email(emailSize, '\0');
    inf.read(reinterpret_cast<char*>(&email[0]), emailSize);

    // read password *super secret style*
    size_t passSize;
    inf.read(reinterpret_cast<char*>(&passSize), sizeof(size_t));
    std::string password(passSize, '\0'); 
    inf.read(reinterpret_cast<char*>(&password[0]), passSize);

    outPlayer = new Player{email, password};

	size_t gamesSize;
	inf.read(reinterpret_cast<char*>(&gamesSize), sizeof(size_t));
	for (int i=0; i<gamesSize; i++)
	{
		size_t gameSize;
		inf.read(reinterpret_cast<char*>(&gameSize), sizeof(size_t));
		std::string newGame(gameSize, '\0');
		inf.read(reinterpret_cast<char*>(&newGame[0]), gameSize);
		outPlayer->m_ownedGames.push_back(newGame);
	}	
}

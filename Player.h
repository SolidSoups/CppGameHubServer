//
// Created by wiley on 3/8/2025.
//

#pragma once
#include <string>
#include <vector>

#include "Game.h"

class Player {
private:
	std::string m_email;
	std::string m_password;

	std::vector<std::string> m_ownedGames;

public:
	Player(const std::string& email, const std::string& password)
		: m_email(email),
	m_password(password)
	{
		m_ownedGames = std::vector<std::string>();
	}

	bool login(const std::string& password);

	void addGame(const Game& newGame);

	std::string getEmail();

	void save(std::ofstream& outf);
	const std::vector<std::string>& getGames();
	static void load(std::ifstream& inf, Player*& outPlayer);
};

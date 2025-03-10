//
// Created by wiley on 3/3/2025.
//

#include "GameHubServer.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::string getAction(const TokenType& type)
{
	return tokenToStringNameMap.at(type);
}

bool GameHubServer::doesUserExist(const std::string& email, size_t& outIndexFound)
{
	bool foundTheUser = false;
	for (int i = 0; i < m_users->size(); i++)
	{
		if (m_users->at(i)->getEmail() == email)
		{
			outIndexFound = i;
			return true;
		}
	}
	return false;
}

bool GameHubServer::doesPlayerExist(const std::string& email, size_t& outIndexFound)
{
	bool foundTheUser = false;
	for (int i = 0; i < m_players->size(); i++)
	{
		if (m_players->at(i)->getEmail() == email)
		{
			outIndexFound = i;
			return true;
		}
	}
	return false;
}

bool GameHubServer::doesGameExist(const std::string& name, size_t& outIndexFound)
{
	bool foundTheGame = false;
	for (int i = 0; i < m_games->size(); i++)
	{
		if (m_games->at(i)->m_name == name)
		{
			outIndexFound = i;
			return true;
		}
	}
	return false;
}

void GameHubServer::Initialize()
{
	m_users = new std::vector<User*>();
	m_players = new std::vector<Player*>();
	m_games = new std::vector<Game*>();
	m_loggedInUser = nullptr;
}


bool GameHubServer::saveDataBase()
{
	std::ofstream outf(fileName);
	if (!outf.is_open())
	{
		std::cerr << "Could not open database for writing" << std::endl;
		return false;
	}

	size_t usersSize = m_users->size();
	outf.write(reinterpret_cast<char*>(&usersSize), sizeof(size_t));
	for (User* user : *m_users)
	{
		user->save(outf);
	}

	size_t playersSize = m_players->size();
	outf.write(reinterpret_cast<char*>(&playersSize), sizeof(size_t));
	for (Player* player : *m_players)
	{
		player->save(outf);
	}

	size_t gameSize = m_games->size();
	outf.write(reinterpret_cast<char*>(&gameSize), sizeof(size_t));
	for (Game* game : *m_games)
	{
		game->save(outf);
	}

	return true;
}

bool GameHubServer::loadDataBase()
{
	std::ifstream inf(fileName);
	if (!inf.is_open())
	{
		std::cerr << "Could not open database for reading" << std::endl;
		return false;
	}

	size_t usersSize;
	inf.read(reinterpret_cast<char*>(&usersSize), sizeof(size_t));
	m_users = new std::vector<User*>(usersSize);
	for (int i = 0; i < usersSize; ++i)
	{
		User* newUser = nullptr;
		User::load(inf, newUser);
		m_users->at(i) = newUser;
	}

	size_t playersSize;
	inf.read(reinterpret_cast<char*>(&playersSize), sizeof(size_t));
	m_players = new std::vector<Player*>(playersSize);
	for (int i = 0; i < playersSize; ++i)
	{
		Player* newPlayer = nullptr;
		Player::load(inf, newPlayer);
		m_players->at(i) = newPlayer;
	}

	size_t gamesSize;
	inf.read(reinterpret_cast<char*>(&gamesSize), sizeof(size_t));
	m_games = new std::vector<Game*>(gamesSize);
	for (int i = 0; i < gamesSize; ++i)
	{
		Game* newGame = nullptr;
		Game::load(inf, newGame);
		m_games->at(i) = newGame;
	}

	inf.close();
	return true;
}

bool GameHubServer::isUserLoggedIn()
{
	return m_loggedInUser != nullptr;
}

bool GameHubServer::isAdminLoggedIn()
{
	return isUserLoggedIn() && m_loggedInUser->isAdmin();
}

GameHubServer::GameHubServer()
	: m_users(new std::vector<User*>()),
	  m_players(new std::vector<Player*>()),
	  m_games(new std::vector<Game*>()),
	  m_loggedInUser(nullptr),
	  m_loggedInPlayer(nullptr)
{
	Initialize();
	loadDataBase();
}

// NOTE: added S409 if we could not save the file
Response GameHubServer::createDataBase(const std::string& adminEmail, const std::string& adminPassword)
{
	Response r{getAction(CREATE_DATABASE)};

	Initialize();
	//TODO: validate email
	User* newUser = new User(adminEmail, adminPassword, true);
	m_users->push_back(newUser);
	if (!saveDataBase()) // NOTE: added conflict response if not able to save
		return r.complete(S409, "Conflict - Couldn't save database");
	return r.complete(S200, "OK - Succeeded");
}

Response GameHubServer::loginUser(const std::string& email, const std::string& password)
{
	Response r{getAction(LOGIN_USER)};

	//TODO: validate email

	size_t outIndex;
	if (!doesUserExist(email, outIndex))
		return r.complete(S401, "Bad Request - User not found");
	User* foundUser = m_users->at(outIndex);

	if (!foundUser->login(password))
		return r.complete(S401, "Unauthorized - Missing Permissions");

	m_loggedInUser = foundUser;

	return r.complete(S200, "OK - Login succeeded");
}

Response GameHubServer::addAdmin(const std::string& email, const std::string& password)
{
	Response r{getAction(ADD_ADMIN)};

	if (!isAdminLoggedIn())
		return r.complete(S403, "Forbidden - Missing permissions");

	// TODO: validate email
	size_t outIndex;
	if (doesUserExist(email, outIndex)) // TODO: we could just make the user admin
		return r.complete(S409, "Conflict - User already exists");

	User* newUser = new User(email, password, true);
	m_users->push_back(newUser);
	return r.complete(S201, "Created");
}

Response GameHubServer::getUsers()
{
	Response r{getAction(GET_USERS)};

	if (!isAdminLoggedIn())
		return r.complete(S403, "Forbidden - Missing permissions");

	std::string usersMessage = "";
	std::stringstream ss;
	if (m_users->size() != 0)
	{
		usersMessage = m_users->at(0)->toString();
		ss << m_users->at(0)->toString();
		for (int i = 1; i < m_users->size(); i++)
		{
			ss << "\n" << m_users->at(i)->toString();
		}
		ss << "\n";
	}

	return r.complete(S200, "Success", ss.str());
}

Response GameHubServer::addGame(const std::string& name)
{
	Response r{getAction(ADD_GAME)};

	if (!isAdminLoggedIn())
		return r.complete(S403, "Forbidden - Missing permissions");

	size_t _;
	if (doesGameExist(name, _))
		return r.complete(S409, "Conflict - Game name already exists");

	Game* newGame = new Game(name);
	m_games->push_back(newGame);

	return r.complete(S201, "Created - A new game was created");
}

Response GameHubServer::removeGame(const std::string& name)
{
	Response r{getAction(REMOVE_GAME)};

	if (!isAdminLoggedIn())
		return r.complete(S403, "Forbidden - Missing permissions");

	size_t outIndex;
	if (!doesGameExist(name, outIndex))
		return r.complete(S404, "Not Found - Game not found");

	m_games->erase(m_games->begin() + outIndex);

	return r.complete(S200, "Success - Game was deleted");
}

Response GameHubServer::getGames()
{
	Response r{getAction(GET_GAMES)};

	if (!isUserLoggedIn())
		return r.complete(S403, "Forbidden - Acting user not logged in, or missing permissions");

	std::string gamesMessage = "";
	std::stringstream ss;
	if (m_games->size() != 0)
	{
		ss << m_games->at(0)->toString();
		for (int i = 1; i < m_games->size(); i++)
		{
			ss << "\n" << m_games->at(i)->toString();
		}
		ss << "\n";
	}

	return r.complete(S200, "Retrieved all games", ss.str());
}

Response GameHubServer::loginPlayer(const std::string& playerEmail)
{
	Response r{getAction(LOGIN_PLAYER)};

	size_t playerIndex;
	if (!doesPlayerExist(playerEmail, playerIndex))
	{
		return r.complete(S401, "Unauthorized");
	}

	m_loggedInPlayer = m_players->at(playerIndex);

	return r.complete(S200, "completed");
}

Response GameHubServer::addPlayer(const std::string& playerEmail, const std::string& playerPassword)
{
	Response r{getAction(ADD_PLAYER)};

	size_t _;
	if (doesUserExist(playerEmail, _) || doesPlayerExist(playerEmail, _))
	{
		return r.complete(S409, "Conflict");
	}

	Player* newPlayer = new Player(playerEmail, playerPassword);
	m_players->push_back(newPlayer);
	return r.complete(S201, "Created");
}

Response GameHubServer::buyGame(const std::string& gameName)
{
	Response r{getAction(BUY_GAME)};
	if (!m_loggedInPlayer)
	{
		return r.complete(S403, "Forbidden");
	}

	size_t outIndex;
	if (!doesGameExist(gameName, outIndex))
		return r.complete(S404, "Not found");

	m_loggedInPlayer->addGame(m_games->at(outIndex)->m_name);

	return r.complete(S200, "Success");
}

Response GameHubServer::getOwnedGames()
{
	Response r{getAction(GET_OWNED_GAMES)};

	if (!m_loggedInPlayer)
		return r.complete(S403, "Forbidden");

	std::vector<std::string> games = m_loggedInPlayer->getGames();

	std::string gameString = "";
	if (games.size() != 0)
	{
		gameString += games[0];
		for (int i=1; i<games.size(); i++)
		{
			gameString += "\n" + games[i];
		}
	}
	
	return r.complete(S200, "Success", gameString);
}

Response GameHubServer::addUser(const std::string& email, const std::string& password)
{
	Response r{getAction(ADD_USER)};

	if (!isAdminLoggedIn())
		return r.complete(S403, "Forbidden - Missing permissions");

	size_t _;
	if (doesUserExist(email, _))
		return r.complete(S409, "Conflict - User already exists");

	User* newUser = new User(email, password, false);
	m_users->push_back(newUser);

	return r.complete(S201, "Created - New user was created");
}

Response GameHubServer::removeUser(const std::string& email)
{
	Response r{getAction(REMOVE_USER)};

	if (!isUserLoggedIn() || !isAdminLoggedIn() && m_loggedInUser->getEmail() != email || !isAdminLoggedIn())
		return r.complete(S403, "Forbidden - Acting user not logged in, or missing permissions");

	size_t outIndex;
	if (!doesUserExist(email, outIndex))
		return r.complete(S404, "Not found - User not found");

	m_users->erase(m_users->begin() + outIndex);
	return r.complete(S200, "Success - User was removed");
}

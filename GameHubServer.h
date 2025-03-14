//
// Created by wiley on 3/3/2025.
//

#pragma once
#include <unordered_map>
#include <vector>
#include <sstream>

#include "datatypes.h"
#include "Game.h"
#include "Player.h"
#include "User.h"




class GameHubServer
{
private:
    std::vector<User*>* m_users;
    std::vector<Player*>* m_players;
    std::vector<Game*>* m_games;
    User* m_loggedInUser;
    Player* m_loggedInPlayer;
    const std::string fileName = "database.bin";

    void Initialize();
    bool loadDataBase();

    bool isUserLoggedIn();
    bool isAdminLoggedIn();
    bool doesUserExist(const std::string& email, size_t& outIndexFound);
    bool doesPlayerExist(const std::string& email, size_t& outIndexFound);
    bool doesGameExist(const std::string& name, size_t& outIndexFound);
public:
    bool saveDataBase();
    GameHubServer();
    ~GameHubServer()
    {
        delete m_users;
        m_users = nullptr;

        delete m_players;
        m_players = nullptr;
        
        delete m_games;
        m_games = nullptr;
        
        delete m_loggedInUser;
        m_loggedInUser = nullptr;
    }

    Response createDataBase(const std::string& adminEmail, const std::string& adminPassword);
    Response loginUser(const std::string& email, const std::string& password);
    Response addAdmin(const std::string& email, const std::string& password);
    Response addUser(const std::string& email, const std::string& password);
    Response removeUser(const std::string& email);
    Response getUsers();
    Response addGame(const std::string& name);
    Response removeGame(const std::string& name);
    Response getGames();

    Response loginPlayer(const std::string& playerEmail);
    Response addPlayer(const std::string& playerEmail, const std::string& playerPassword);
    Response buyGame(const std::string& gameName);
    Response getOwnedGames();
};
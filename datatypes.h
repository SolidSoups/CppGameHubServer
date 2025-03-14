//
// Created by wiley on 3/4/2025.
//

#pragma once
#include <unordered_map>
#include <sstream>

enum StatusCode { S200, S201, S400, S401, S403, S404, S409, };

const std::unordered_map<StatusCode, std::string> statusCodeToString{
    {S200, "200"},
    {S201, "201"},
    {S400, "400"},
    {S401, "401"},
    {S403, "403"},
    {S404, "404"},
    {S409, "409"}, 
};

struct Response
{
    Response(const std::string& action) : action(action) {}
    std::string action;
    
    StatusCode status;
    std::string statusMessage;
    std::string dataMessage = "";

    Response complete(const StatusCode& _status, const std::string& _statusMessage)
    {
        status = _status;
        statusMessage = _statusMessage;
        dataMessage = "";
        return *this;
    }  
    Response complete(const StatusCode& _status, const std::string& _statusMessage, const std::string& _dataMessage)
    {
        status = _status;
        statusMessage = _statusMessage;
        dataMessage = _dataMessage;
        return *this;
    }  
    std::string getString()
    {
        std::stringstream ss;
        ss << action << std::endl
           << statusCodeToString.at(status) << std::endl
            << dataMessage << "\n";
        return ss.str();
    }
};

enum TokenType
{
	CREATE_DATABASE,
	LOGIN_USER,
	ADD_ADMIN,
	ADD_USER,
	REMOVE_USER,
	GET_USERS,
	ADD_GAME,
	REMOVE_GAME,
	GET_GAMES,
	ADD_PLAYER,
	LOGIN_PLAYER,
	BUY_GAME,
	GET_OWNED_GAMES,
	HELP,
	_END_DISPLAY_HELP,

	ARG,
};

const std::pmr::unordered_map<std::string, TokenType> stringToTokenMap{
	{"create_database", CREATE_DATABASE},
	{"login", LOGIN_USER},
	{"add_admin", ADD_ADMIN},
	{"add_user", ADD_USER},
	{"remove_user", REMOVE_USER},
	{"get_users", GET_USERS},
	{"add_game", ADD_GAME},
	{"remove_game", REMOVE_GAME},
	{"get_games", GET_GAMES},
	{"add_player", ADD_PLAYER},
	{"login_player", LOGIN_PLAYER},
	{"buy_game", BUY_GAME},
	{"get_owned_games", GET_OWNED_GAMES},
	{"arg", ARG},
	{"help", HELP}
};
const std::pmr::unordered_map<TokenType, std::string> tokenToStringNameMap{
	{CREATE_DATABASE, "create_database"},
	{LOGIN_USER, "login"},
	{ADD_ADMIN, "add_admin"},
	{ADD_USER, "add_user"},
	{REMOVE_USER, "remove_user"},
	{GET_USERS, "get_users"},
	{ADD_GAME, "add_game"},
	{REMOVE_GAME, "remove_game"},
	{GET_GAMES, "get_games"},
	{ADD_PLAYER, "add_player"},
	{LOGIN_PLAYER, "login_player"},
	{BUY_GAME, "buy_game"},
	{GET_OWNED_GAMES, "get_owned_games"},
	{ARG, "arg"},
	{HELP, "help"}
};
const std::pmr::unordered_map<TokenType, std::string> cmdlineHelpTextMap{
	{
		CREATE_DATABASE,
		"create_database [email] [password] : Create a new database with the specified email and password. (admin)"
	},
	{
		LOGIN_USER,
		"login [email] [password] : Login to the database with the specified email and password. (none)"
	},
	{
		ADD_ADMIN,
		"add_admin [email]: Add a new admin user with the specified email. (admin)"
	},
	{
		ADD_USER,
		"add_user [email] [password] : Add a new admin user with the specified email. (admin)"
	},
	{
		REMOVE_USER,
		"remove_user [email] : Remove the user with the specified email. (admin, user)"
	},
	{
		GET_USERS,
		"get_users : Get a list of all users. (admin)"
	},
	{
		ADD_GAME,
		"add_game [name] : Add a new game to the database. (admin)"
	},
	{
		REMOVE_GAME,
		"remove_game [name] : Remove a game from the database. (admin)"
	},
	{
		GET_GAMES,
		"get_games : Get a list of all games. (user)"
	},
	{
		ADD_PLAYER,
		"add_player [email] [password] : Add a player. (none)"
	},
	{
		LOGIN_PLAYER,
		"login_player [email] [password] : Login as a player. (none)"
	},
	{
		BUY_GAME,
		"buy_game [name] : Buy a game. (Player)"
	},
	{
		GET_OWNED_GAMES,
		"get_owned_games : Get owned games. (Player)"
	},
	{
		HELP,
		"help (optional)[command]: Display a helpful message."
	}
};

struct Token
{
	TokenType m_type;
	std::string m_value;
};

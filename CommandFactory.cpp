//
// Created by wiley on 3/4/2025.
//

#include "CommandFactory.h"

CommandFactory::CommandPtr CommandFactory::Create(TokenType type)
{
	static std::pmr::unordered_map<TokenType, std::function<CommandPtr()>> commandMap = {
		{TokenType::CREATE_DATABASE, []() { return std::make_unique<CreateDataBase_ServerCommand>(); }},
		{TokenType::LOGIN_USER, []() { return std::make_unique<Login_ServerCommand>(); }},
		{TokenType::ADD_ADMIN, []() { return std::make_unique<AddAdmin_ServerCommand>(); }},
		{TokenType::ADD_USER, []() { return std::make_unique<AddUser_ServerCommand>(); }},
		{TokenType::REMOVE_USER, []() { return std::make_unique<RemoveUser_ServerCommand>(); }},
		{TokenType::GET_USERS, []() { return std::make_unique<GetUsers_ServerCommand>(); }},
		{TokenType::ADD_GAME, []() { return std::make_unique<AddGame_ServerCommand>(); }},
		{TokenType::REMOVE_GAME, []() { return std::make_unique<RemoveGame_ServerCommand>(); }},
		{ADD_PLAYER, []() { return std::make_unique<AddPlayer_ServerCommand>(); }},
		{LOGIN_PLAYER, []() {return std::make_unique<LoginPlayer_ServerCommand>(); }},
		{BUY_GAME, []() {return std::make_unique<BuyGame_ServerCommand>(); }},
		{GET_OWNED_GAMES, []() {return std::make_unique<GetOwnedGames_ServerCommand>(); }},
		{TokenType::GET_GAMES, []() { return std::make_unique<GetGames_ServerCommand>(); }},
	};

	auto it = commandMap.find(type);
	if (it != commandMap.end())
	{
		return it->second();
	}
	return nullptr;
}

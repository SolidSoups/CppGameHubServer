//
// Created by wiley on 3/4/2025.
//

#pragma once
#include <string>

#include "datatypes.h"
#include "GameHubServer.h"

class IServerCommand
{
public:
	virtual Response Execute(GameHubServer& server) = 0;
	virtual ~IServerCommand() = default;
};

class NoArgServerCommand : public IServerCommand{};
class OneArgServerCommand : public IServerCommand
{
public:
	std::string arg0;
};
class TwoArgServerCommand : public IServerCommand
{
public:
	std::string arg0;
	std::string arg1;
};

// implementations
class CreateDataBase_ServerCommand : public TwoArgServerCommand
{
public:
	CreateDataBase_ServerCommand() {}
	Response Execute(GameHubServer& server) override;
};

class Login_ServerCommand : public TwoArgServerCommand
{
public:
	Login_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class AddAdmin_ServerCommand : public TwoArgServerCommand
{
public:
	AddAdmin_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class AddUser_ServerCommand : public TwoArgServerCommand
{
public:
	AddUser_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class RemoveUser_ServerCommand : public OneArgServerCommand
{
public:
	RemoveUser_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class GetUsers_ServerCommand : public NoArgServerCommand
{
public:
	GetUsers_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class AddGame_ServerCommand : public OneArgServerCommand
{
public:
	AddGame_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class RemoveGame_ServerCommand : public OneArgServerCommand
{
public:
	RemoveGame_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class GetGames_ServerCommand : public NoArgServerCommand
{
public:
	GetGames_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class AddPlayer_ServerCommand : public TwoArgServerCommand
{
public:
	AddPlayer_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class LoginPlayer_ServerCommand : public OneArgServerCommand
{
public:
	LoginPlayer_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class BuyGame_ServerCommand : public OneArgServerCommand
{
public:
	BuyGame_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

class GetOwnedGames_ServerCommand : public NoArgServerCommand
{
public:
	GetOwnedGames_ServerCommand(){}
	Response Execute(GameHubServer& server) override;
};

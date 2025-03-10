//
// Created by wiley on 3/4/2025.
//

#include "Command.h"

#include <iostream>

#include "GameHubServer.h"


Response CreateDataBase_ServerCommand::Execute(GameHubServer& server)
{
	return server.createDataBase(arg0, arg1);	
}

Response Login_ServerCommand::Execute(GameHubServer& server)
{
	return server.loginUser(arg0, arg1);
}

Response AddAdmin_ServerCommand::Execute(GameHubServer& server)
{
	return server.addAdmin(arg0, arg1);
}

Response AddUser_ServerCommand::Execute(GameHubServer& server)
{
	return server.addUser(arg0, arg1);
}

Response RemoveUser_ServerCommand::Execute(GameHubServer& server)
{
	return server.removeUser(arg0);
}

Response GetUsers_ServerCommand::Execute(GameHubServer& server)
{
	return server.getUsers();
}

Response AddGame_ServerCommand::Execute(GameHubServer& server)
{
	return server.addGame(arg0);
}

Response RemoveGame_ServerCommand::Execute(GameHubServer& server)
{
	return server.removeGame(arg0);
}

Response GetGames_ServerCommand::Execute(GameHubServer& server)
{
	return server.getGames();
}

Response AddPlayer_ServerCommand::Execute(GameHubServer& server)
{
	return server.addPlayer(arg0, arg1);
}

Response LoginPlayer_ServerCommand::Execute(GameHubServer& server)
{
	return server.loginPlayer(arg0);
}

Response BuyGame_ServerCommand::Execute(GameHubServer& server)
{
	return server.buyGame(arg0);
}

Response GetOwnedGames_ServerCommand::Execute(GameHubServer& server)
{
	return server.getOwnedGames();
}

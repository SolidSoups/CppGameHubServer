//
// Created by wiley on 3/4/2025.
//

#pragma once
#include <vector>
#include <iostream>

#include "datatypes.h"
#include "GameHubServer.h"


class TokenParser {
public:
	TokenParser(const std::vector<Token>& tokens)
		: tokens(tokens),
		  pos(0)
	{
		server = new GameHubServer();
	}
	void startParsingTokens();
private:
	std::vector<Token> tokens;
	GameHubServer* server; 
	size_t pos;

	Token peek() { return tokens[pos]; }
	Token advance() { return tokens[pos++]; }

	void iterateTokens();
	// TODO: implement this
	bool executeCommand(const Token& cmdToken, const std::vector<Token>& argTokens);
};

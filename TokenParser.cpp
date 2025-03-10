//
// Created by wiley on 3/4/2025.
//

#include "TokenParser.h"

#include <complex>

#include "CommandFactory.h"
#include <sstream>

// #define _DEBUG

void coutDebug(const std::string& message)
{
#ifdef _DEBUG
	std::cout << message << std::endl;
#endif
}

/// Starts parsing tokens
void TokenParser::startParsingTokens()
{
	if (peek().m_type == ARG)
	{
		std::cerr << "First token is an argument" << std::endl;
		return;
	}
	coutDebug("-First token is not arg");
	if (peek().m_type == HELP)
	{
		// display help
		size_t t_size = tokens.size();
		if (t_size == 1)
		{
			std::cout << "Help for the following commands:" << std::endl;
			for (int i = CREATE_DATABASE; i < _END_DISPLAY_HELP; i++)
			{
				std::cout << " - " << cmdlineHelpTextMap.at(static_cast<TokenType>(i)) << std::endl;
			}
		}
		else if (t_size == 2 && tokens[1].m_type != ARG)
		{
			std::cout << "Help for the following command:" << std::endl;
			std::cout << " - " << cmdlineHelpTextMap.at(tokens[1].m_type) << std::endl;
		}
		else
		{
			std::cout << "Incorrect usage of help. Please use 'help [cmd]'." << std::endl;
		}
		return;
	}
	coutDebug("-First token is not help");

	iterateTokens();
}

/// Outputs a response to a bad parameter
void coutBadParameter(const std::string& action, const std::string& sMessage = "Bad Request - Parameter is incorrect")
{
	std::cout << Response{action}
	             .complete(S400, sMessage)
	             .getString() << std::endl;
}

/// Iterates through the tokens, parsing commands and then args in succession
void TokenParser::iterateTokens()
{
	Token cmdToken = advance();
	std::vector<Token> argTokens;
	bool commandsFailed = false;
	while (pos <= tokens.size())
	{
		if (pos == tokens.size() || peek().m_type != ARG) // start executing command
		{
			if (!executeCommand(cmdToken, argTokens))
			{
				break;
			}

			if (pos == tokens.size())
			{
				commandsFailed = true;
				break;
			}

			cmdToken = advance();
			argTokens.clear();
			continue;
		}

		argTokens.push_back(advance());
	}

	if (commandsFailed)
	{
		server->saveDataBase();
	}
}

// Validates the arguments expected for a command to execute
bool validateCommandArguments(size_t expected, const std::vector<Token>& argTokens, const std::string& cmdName)
{
	size_t argSize = argTokens.size();
	if (expected <= argSize)
		return true;
	std::stringstream ss;
	ss << cmdName;
	coutBadParameter(ss.str());
	return false;
}

/// Determines if a command can be executed, gives it the correct parameters and executes it.
bool TokenParser::executeCommand(const Token& cmdToken, const std::vector<Token>& argTokens)
{
	auto command = CommandFactory::Create(cmdToken.m_type); // create command from TokenType
	if (!command) // command not found
	{
		return false;
	}

	// cast to all possible subclasses
	auto noArgsCmd = dynamic_cast<NoArgServerCommand*>(command.get());
	auto oneArgCmd = dynamic_cast<OneArgServerCommand*>(command.get());
	auto twoArgsCmd = dynamic_cast<TwoArgServerCommand*>(command.get());

	// validate and fill args
	size_t argsUsed = 0;
	if (noArgsCmd)
	{
		if (!validateCommandArguments(0, argTokens, cmdToken.m_value))
			return false;
	}
	else if (oneArgCmd)
	{
		if (!validateCommandArguments(1, argTokens, cmdToken.m_value))
			return false;

		oneArgCmd->arg0 = argTokens[0].m_value;
		argsUsed = 1;
	}
	else if (twoArgsCmd)
	{
		if (!validateCommandArguments(2, argTokens, cmdToken.m_value))
			return false;

		twoArgsCmd->arg0 = argTokens[0].m_value;
		twoArgsCmd->arg1 = argTokens[1].m_value;
		argsUsed = 2;
	}

	// execute command and get response
	Response rsp = command->Execute(*server);
	std::cout << rsp.getString();

	// check if we need to step back
	if (argTokens.size() > argsUsed)
	{
		step_back(argTokens.size() - argsUsed);
	}

	return rsp.status == S200 || rsp.status == S201;
}

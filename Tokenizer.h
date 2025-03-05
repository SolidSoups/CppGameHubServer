//
// Created by wiley on 3/3/2025.
//
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "datatypes.h"


class Tokenizer
{
public:
	explicit Tokenizer(const int& argc, char* argv[])
	{
		m_argv.assign(argv, argv + argc);
	}

	std::vector<Token> tokenize();

	static std::string getTokenString(const std::vector<Token> tokens)
	{
		std::string tokenString;
		for (int i = 0; i < tokens.size(); i++)
		{
			std::string tokenType = tokenToStringNameMap.at(tokens[i].m_type);
			tokenString += "[" + tokenType + "] ";
		}
		return tokenString;
	}

private:
	std::vector<char*> m_argv;
};

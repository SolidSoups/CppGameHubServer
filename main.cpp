#include <crtdbg.h>
#include <fstream>
#include <iostream>
#include "Tokenizer.h"
#include "TokenParser.h"

// #define _DEBUG

void coutDebug(std::string str)
{
#ifdef _DEBUG
    std::cout << str << std::endl;
#endif
}

std::vector<Token> getTokens(const int& argc, char* argv[])
{
    Tokenizer newTokenizer(argc, argv);
    return newTokenizer.tokenize();
}

// #define _BUILD
int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);    

#ifdef _BUILD
    int mock_argc = 15;
    const char* mock_argv[] = {"program_name", "create_database", "e", "p", "add_player", "ep", "pp", "login", "e", "p", "login_player", "ep", "add_game", "Snake", "get_owned_games" };
    std::vector<Token> tokens = getTokens(mock_argc, const_cast<char**>(mock_argv));
#else
    std::vector<Token> tokens = getTokens(argc, argv);
#endif

    if (tokens.size() != 0)
    {
        coutDebug(
            "Tokenized input: " + Tokenizer::getTokenString(tokens) + "(" + std::to_string(tokens.size()) + ")\n");

        TokenParser* tokenParser = new TokenParser(tokens);
        tokenParser->startParsingTokens();
    }

    

#ifdef _BUILD
    std::cin.get();
#endif

    return 0;
}

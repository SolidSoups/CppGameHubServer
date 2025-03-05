//
// Created by wiley on 3/3/2025.
//

#include "Tokenizer.h"

#include <iostream>


std::vector<Token> Tokenizer::tokenize()
{
        std::vector<Token> tokens;

        for (int i=1; i< m_argv.size(); i++)
        {
            char* arg = m_argv[i];
            
            Token newToken;
            newToken.m_value = arg;

            if (stringToTokenMap.find(arg) != stringToTokenMap.end())
            {
               newToken.m_type = stringToTokenMap.at(arg); 
            }
            else
            {
                newToken.m_type = ARG;
            }

            tokens.push_back(newToken);
        }
        
        return tokens;
}
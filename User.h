//
// Created by wiley on 3/3/2025.
//

#pragma once
#include <string>
#include <sstream>

class User {
private:
    std::string m_email;
    std::string m_password;
    bool m_bAdmin;
public:
    User(const std::string& email, const std::string& password, const bool& bAdmin) : m_email(email), m_password(password), m_bAdmin(bAdmin) {}
    bool login(const std::string password);
    std::string getEmail();
    bool isAdmin();

    void save(std::ofstream& outf);
    static void load(std::ifstream& inf, User*& outUser);

    std::string toString()
    {
        std::stringstream ss;
        ss << (m_bAdmin?0:1) << ":" << m_email;  
        return ss.str();
    }
};

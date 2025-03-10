//
// Created by wiley on 3/3/2025.
//

#include "User.h"
#include <fstream>

/// Secure login procedure
bool User::login(const std::string password) 
{
   if (m_password == password)
	   return true;
	return false;
}

std::string User::getEmail() { return m_email; }
bool User::isAdmin() { return m_bAdmin; }

void User::save(std::ofstream& outf)
{
    // write email
    size_t emailSize = m_email.size();
    outf.write(reinterpret_cast<char*>(&emailSize), sizeof(size_t));
    outf.write(m_email.c_str(), emailSize);

    // write password *super secret style*
    size_t passSize = m_password.size();
    outf.write(reinterpret_cast<char*>(&passSize), sizeof(size_t));
    outf.write(m_password.c_str(), passSize);

    // write isAdmin
    outf.write(reinterpret_cast<char*>(&m_bAdmin), sizeof(bool));

}

void User::load(std::ifstream& inf, User*& outUser)
{
    // read email
    size_t emailSize;
    inf.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
    std::string email(emailSize, '\0');
    inf.read(reinterpret_cast<char*>(&email[0]), emailSize);

    // read password *super secret style*
    size_t passSize;
    inf.read(reinterpret_cast<char*>(&passSize), sizeof(size_t));
    std::string password(passSize, '\0'); 
    inf.read(reinterpret_cast<char*>(&password[0]), passSize);

    // read isAdmin
    bool isAdmin(0);
    inf.read(reinterpret_cast<char*>(&isAdmin), sizeof(bool));

    outUser = new User{email, password, isAdmin};
}


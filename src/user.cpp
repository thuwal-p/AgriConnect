
#include "../include/user.h"

User::User()
{
    username = "";
    password = "";
}

User::User(string u, string p)
{
    username = u;
    password = p;
}

string User::getUsername()
{
    return username;
}

string User::getPassword()
{
    return password;
}

void UserAuthentication::loadFarmers()
{
    ifstream file("farmers.txt");
    string username, password;

    while (file >> username >> password)
    {
        farmerUsers[username] = User(username, password);
    }

    file.close();
}

void UserAuthentication::loadMandis()
{
    ifstream file("mandis.txt");
    string username, password;

    while (file >> username >> password)
    {
        mandiUsers[username] = User(username, password);
    }

    file.close();
}

bool UserAuthentication::farmerLogin(string username, string password)
{
    auto it = farmerUsers.find(username);

    if (it != farmerUsers.end() &&
        it->second.getPassword() == password)
    {
        return true;
    }

    return false;
}

bool UserAuthentication::mandiLogin(string username, string password)
{
    auto it = mandiUsers.find(username);

    if (it != mandiUsers.end() &&
        it->second.getPassword() == password)
    {
        return true;
    }

    return false;
}
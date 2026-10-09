

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
    farmerUsers.clear();

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
    mandiUsers.clear();

    ifstream file("mandis.txt");

    string username, password;

    while (file >> username >> password)
    {
        mandiUsers[username] = User(username, password);
    }

    file.close();
}

bool UserAuthentication::registerFarmer(string username, string password)
{
    if (username.empty() || password.empty())
        return false;

    if (farmerUsers.find(username) != farmerUsers.end())
        return false;

    ofstream file("farmers.txt", ios::app);

    if (!file.is_open())
        return false;

    file << username << " " << password << "\n";
    file.close();

    farmerUsers[username] = User(username, password);

    return true;
}

bool UserAuthentication::registerMandi(string username, string password)
{
    if (username.empty() || password.empty())
        return false;

    if (mandiUsers.find(username) != mandiUsers.end())
        return false;

    ofstream file("mandis.txt", ios::app);

    if (!file.is_open())
        return false;

    file << username << " " << password << "\n";
    file.close();

    mandiUsers[username] = User(username, password);

    return true;
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

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
    string u, p;

    while (file >> u >> p)
    {
        farmerUsers[u] = User(u, p);
    }

    file.close();
}

void UserAuthentication::loadMandis()
{
    ifstream file("mandis.txt");
    string u, p;

    while (file >> u >> p)
    {
        mandiUsers[u] = User(u, p);
    }

    file.close();
}

bool UserAuthentication::farmerUsernameExists(string u)
{
    if (farmerUsers.count(u) == 1)
        return true;
    else
        return false;
}

bool UserAuthentication::mandiUsernameExists(string u)
{
    if (mandiUsers.count(u) == 1)
        return true;
    else
        return false;
}

bool UserAuthentication::farmerLogin(string u, string p)
{
    if (farmerUsers.count(u) == 1)
    {
        if (farmerUsers[u].getPassword() == p)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool UserAuthentication::mandiLogin(string u, string p)
{
    if (mandiUsers.count(u) == 1)
    {
        if (mandiUsers[u].getPassword() == p)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool UserAuthentication::registerFarmer(string u, string p)
{
    if (farmerUsers.count(u) == 1)
        return false;

    ofstream file("farmers.txt", ios::app);

    if (!file)
        return false;

    file << u << " " << p << "\n";
    file.close();

    farmerUsers[u] = User(u, p);

    return true;
}

bool UserAuthentication::registerMandi(string u, string p)
{
    if (mandiUsers.count(u) == 1)
        return false;

    ofstream file("mandis.txt", ios::app);

    if (!file)
        return false;

    file << u << " " << p << "\n";
    file.close();

    mandiUsers[u] = User(u, p);

    return true;
}

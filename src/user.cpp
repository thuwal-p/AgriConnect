
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

UserAuthentication::UserAuthentication()
{
    farmerCount = 0;
    mandiCount = 0;
}

void UserAuthentication::loadFarmers()
{
    ifstream file("farmers.txt");
    string u, p;

    farmerCount = 0;

    while (file >> u >> p)
    {
        if (farmerCount < 100)
        {
            farmerNames[farmerCount] = u;
            farmerPasswords[farmerCount] = p;
            farmerCount++;
        }
    }

    file.close();
}

void UserAuthentication::loadMandis()
{
    ifstream file("mandis.txt");
    string u, p;

    mandiCount = 0;

    while (file >> u >> p)
    {
        if (mandiCount < 100)
        {
            mandiNames[mandiCount] = u;
            mandiPasswords[mandiCount] = p;
            mandiCount++;
        }
    }

    file.close();
}

bool UserAuthentication::farmerLogin(string u, string p)
{
    int i = 0;

    while (i < farmerCount)
    {
        if (farmerNames[i] == u &&
            farmerPasswords[i] == p)
        {
            return true;
        }

        i++;
    }

    return false;
}

bool UserAuthentication::mandiLogin(string u, string p)
{
    int i = 0;

    while (i < mandiCount)
    {
        if (mandiNames[i] == u &&
            mandiPasswords[i] == p)
        {
            return true;
        }

        i++;
    }

    return false;
}

bool UserAuthentication::registerFarmer(string u, string p)
{
    int i = 0;

    while (i < farmerCount)
    {
        if (farmerNames[i] == u)
        {
            return false;
        }

        i++;
    }

    if (farmerCount >= 100)
    {
        return false;
    }

    ofstream file("farmers.txt", ios::app);

    if (!file)
    {
        return false;
    }

    file << u << " " << p << "\n";
    file.close();

    farmerNames[farmerCount] = u;
    farmerPasswords[farmerCount] = p;
    farmerCount++;

    return true;
}

bool UserAuthentication::registerMandi(string u, string p)
{
    int i = 0;

    while (i < mandiCount)
    {
        if (mandiNames[i] == u)
        {
            return false;
        }

        i++;
    }

    if (mandiCount >= 100)
    {
        return false;
    }

    ofstream file("mandis.txt", ios::app);

    if (!file)
    {
        return false;
    }

    file << u << " " << p << "\n";
    file.close();

    mandiNames[mandiCount] = u;
    mandiPasswords[mandiCount] = p;
    mandiCount++;

    return true;
}

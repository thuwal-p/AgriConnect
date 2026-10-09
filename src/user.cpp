
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

<<<<<<< HEAD
UserAuthentication::UserAuthentication()
{
    farmerCount = 0;
    mandiCount = 0;
}

=======
>>>>>>> 01d5478 (Improve authentication and registration)
void UserAuthentication::loadFarmers()
{
    ifstream file("farmers.txt");
    string u, p;

<<<<<<< HEAD
    farmerCount = 0;

    while (file >> u >> p)
    {
        if (farmerCount < 100)
        {
            farmerNames[farmerCount] = u;
            farmerPasswords[farmerCount] = p;
            farmerCount++;
        }
=======
    while (file >> u >> p)
    {
        farmerUsers[u] = User(u, p);
>>>>>>> 01d5478 (Improve authentication and registration)
    }

    file.close();
}

void UserAuthentication::loadMandis()
{
    ifstream file("mandis.txt");
    string u, p;

<<<<<<< HEAD
    mandiCount = 0;

    while (file >> u >> p)
    {
        if (mandiCount < 100)
        {
            mandiNames[mandiCount] = u;
            mandiPasswords[mandiCount] = p;
            mandiCount++;
        }
=======
    while (file >> u >> p)
    {
        mandiUsers[u] = User(u, p);
>>>>>>> 01d5478 (Improve authentication and registration)
    }

    file.close();
}

<<<<<<< HEAD
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
=======
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
>>>>>>> 01d5478 (Improve authentication and registration)
}

bool UserAuthentication::mandiLogin(string u, string p)
{
<<<<<<< HEAD
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
=======
    if (mandiUsers.count(u) == 1)
    {
        if (mandiUsers[u].getPassword() == p)
            return true;
        else
            return false;
    }
    else
        return false;
>>>>>>> 01d5478 (Improve authentication and registration)
}

bool UserAuthentication::registerFarmer(string u, string p)
{
<<<<<<< HEAD
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
=======
    if (farmerUsers.count(u) == 1)
        return false;
>>>>>>> 01d5478 (Improve authentication and registration)

    ofstream file("farmers.txt", ios::app);

    if (!file)
<<<<<<< HEAD
    {
        return false;
    }
=======
        return false;
>>>>>>> 01d5478 (Improve authentication and registration)

    file << u << " " << p << "\n";
    file.close();

<<<<<<< HEAD
    farmerNames[farmerCount] = u;
    farmerPasswords[farmerCount] = p;
    farmerCount++;
=======
    farmerUsers[u] = User(u, p);
>>>>>>> 01d5478 (Improve authentication and registration)

    return true;
}

bool UserAuthentication::registerMandi(string u, string p)
{
<<<<<<< HEAD
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
=======
    if (mandiUsers.count(u) == 1)
        return false;
>>>>>>> 01d5478 (Improve authentication and registration)

    ofstream file("mandis.txt", ios::app);

    if (!file)
<<<<<<< HEAD
    {
        return false;
    }
=======
        return false;
>>>>>>> 01d5478 (Improve authentication and registration)

    file << u << " " << p << "\n";
    file.close();

<<<<<<< HEAD
    mandiNames[mandiCount] = u;
    mandiPasswords[mandiCount] = p;
    mandiCount++;
=======
    mandiUsers[u] = User(u, p);
>>>>>>> 01d5478 (Improve authentication and registration)

    return true;
}

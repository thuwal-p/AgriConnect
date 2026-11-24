
#include "../include/user.h"

// Reads one "key value" record per line. Tolerates CRLF, a UTF-8 BOM, blank
// lines and malformed lines (they are skipped instead of derailing the file).
static void loadCredentialFile(const char* path, unordered_map<string, User>& out)
{
    ifstream file(path);
    string u, p;

    while (file >> u >> p)
    {
        out[u] = User(u, p);
    }

    file.close();
}

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
    loadCredentialFile("farmers.txt", farmerUsers);
}

void UserAuthentication::loadMandis()
{
    loadCredentialFile("mandis.txt", mandiUsers);
}

bool UserAuthentication::farmerUsernameExists(string u)//duplicate check while registrarion
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

    ofstream file("farmers.txt", ios::app);//file is opened in append mode

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

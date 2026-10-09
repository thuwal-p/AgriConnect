
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

class User
{
private:
    string username;
    string password;

public:
    User();
    User(string u, string p);

    string getUsername();
    string getPassword();
};

class UserAuthentication
{
private:
    unordered_map<string, User> farmerUsers;
    unordered_map<string, User> mandiUsers;

public:
    void loadFarmers();
    void loadMandis();

    bool farmerUsernameExists(string u);
    bool mandiUsernameExists(string u);

    bool farmerLogin(string u, string p);
    bool mandiLogin(string u, string p);

    bool registerFarmer(string u, string p);
    bool registerMandi(string u, string p);
};

#endif




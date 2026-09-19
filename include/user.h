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

    bool farmerLogin(string username, string password);
    bool mandiLogin(string username, string password);
};

#endif
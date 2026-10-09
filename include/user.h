
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
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
    string farmerNames[100];
    string farmerPasswords[100];

    string mandiNames[100];
    string mandiPasswords[100];

    int farmerCount;
    int mandiCount;

public:
    UserAuthentication();

    void loadFarmers();
    void loadMandis();

<<<<<<< HEAD
=======
    bool farmerUsernameExists(string u);
    bool mandiUsernameExists(string u);

>>>>>>> 01d5478 (Improve authentication and registration)
    bool farmerLogin(string u, string p);
    bool mandiLogin(string u, string p);

    bool registerFarmer(string u, string p);
    bool registerMandi(string u, string p);
};

#endif




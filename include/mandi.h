#ifndef MANDI_H
#define MANDI_H

#include "user.h"
#include <string>

using namespace std;

class Mandi : public User
{
private:
    string mandiName;
    string location;

public:
    // Constructors
    Mandi();
    Mandi(string u, string p, string name, string loc);

    // Setters
    void setMandiName(string name);
    void setLocation(string loc);

    // Getters
    string getMandiName();
    string getLocation();

    // Mandi management functions
    bool addMandi();
    bool viewMandi(string id);
    bool updateMandi(string id, string name, string loc);
    bool searchMandi(string id);
};

#endif
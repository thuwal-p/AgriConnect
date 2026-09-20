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
    Mandi();
    Mandi(string u, string p, string name, string loc);

    void setMandiName(string name);
    void setLocation(string loc);

    string getMandiName();
    string getLocation();
};

#endif
#ifndef FARMER_H
#define FARMER_H

#include "user.h"
#include <string>

using namespace std;

class Farmer : public User
{
private:
    string farmerName;
    string location;

public:
    Farmer();
    Farmer(string u, string p, string name, string loc);

    void setFarmerName(string name);
    void setLocation(string loc);

    string getFarmerName();
    string getLocation();
};

#endif
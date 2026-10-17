#ifndef MANDI_H
#define MANDI_H

#include "user.h"
#include <string>
#include <vector>

using namespace std;

class Mandi : public User
{
private:
    string mandiName;
    string location;
    vector<string> crops;
    int capacity;

public:
    // Constructors
    Mandi();
    Mandi(string u, string p, string name, string loc,
          vector<string> crops, int capacity);

    // Setters
    void setMandiName(string name);
    void setLocation(string loc);
    void setCrops(vector<string> crops);
    void setCapacity(int capacity);

    // Getters
    string getMandiName();
    string getLocation();
    vector<string> getCrops();
    int getCapacity();

    // Mandi management functions
    bool addMandi();
    bool viewMandi(string id);
    bool updateMandi(string id, string name, string loc);
    bool searchMandi(string id);
};

#endif
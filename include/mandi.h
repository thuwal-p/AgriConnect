
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
    vector<double> buyingPrices;
    int capacity;

public:
    Mandi();
    Mandi(string u, string p, string name, string loc,
          vector<string> crops, vector<double> prices, int capacity);

    void setMandiName(string name);
    void setLocation(string loc);
    void setCrops(vector<string> crops);
    void setBuyingPrices(vector<double> prices);
    void setCapacity(int capacity);

    string getMandiName();
    string getLocation();
    vector<string> getCrops() const;
    vector<double> getBuyingPrices() const;
    int getCapacity();

    bool addMandi();
    bool viewMandi(string id);
    bool updateMandi(string id);
    bool updateMandiCapacity(string id, int newCapacity);
    vector<Mandi> getAllMandis();
};

#endif


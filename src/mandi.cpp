
#include "../include/mandi.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

Mandi::Mandi()
{
    mandiName = "";
    location = "";
    crops.clear();
    buyingPrices.clear();
    capacity = 0;
}

Mandi::Mandi(string u, string p, string name, string loc,
             vector<string> c, vector<double> prices, int cap)
    : User(u, p)
{
    mandiName = name;
    location = loc;
    crops = c;
    buyingPrices = prices;
    capacity = cap;
}

void Mandi::setMandiName(string name)
{
    mandiName = name;
}

void Mandi::setLocation(string loc)
{
    location = loc;
}

void Mandi::setCrops(vector<string> c)
{
    crops = c;
}

void Mandi::setBuyingPrices(vector<double> prices)
{
    buyingPrices = prices;
}

void Mandi::setCapacity(int cap)
{
    capacity = cap;
}

string Mandi::getMandiName()
{
    return mandiName;
}

string Mandi::getLocation()
{
    return location;
}

vector<string> Mandi::getCrops()
{
    return crops;
}

vector<double> Mandi::getBuyingPrices()
{
    return buyingPrices;
}

int Mandi::getCapacity()
{
    return capacity;
}

bool Mandi::addMandi()
{
    string id = getUsername();
    string u, name, loc, cropData;
    int cap;

    if (id == "" || mandiName == "" || location == "")
        return false;

    if (crops.size() != buyingPrices.size())
        return false;

    ifstream check("mandi_details.txt");

    while (check >> u >> name >> loc >> cap >> cropData)
    {
        if (u == id)
        {
            check.close();
            return false;
        }
    }
    check.close();

    ofstream file("mandi_details.txt", ios::app);

    if (!file)
        return false;

    file << id << " " << mandiName << " "
         << location << " " << capacity << " ";

    for (int i = 0; i < (int)crops.size(); i++)
    {
        file << crops[i] << ":" << buyingPrices[i];

        if (i < (int)crops.size() - 1)
            file << ",";
    }

    file << "\n";
    file.close();

    return true;
}

bool Mandi::viewMandi(string id)
{
    ifstream file("mandi_details.txt");

    string u, name, loc, cropData;
    int cap;

    if (!file)
        return false;

    while (file >> u >> name >> loc >> cap >> cropData)
    {
        if (u == id)
        {
            cout << "Mandi Username: " << u << endl;
            cout << "Name: " << name << endl;
            cout << "Location: " << loc << endl;
            cout << "Capacity: " << cap << endl;
            cout << "Crop Buying Prices:" << endl;

            stringstream ss(cropData);
            string item;

            while (getline(ss, item, ','))
            {
                size_t pos = item.find(':');

                if (pos != string::npos)
                {
                    cout << item.substr(0, pos)
                         << " - Rs. " << item.substr(pos + 1)
                         << endl;
                }
            }

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool Mandi::updateMandi(string id, string name, string loc)
{
    ifstream file("mandi_details.txt");

    if (!file)
        return false;

    string ids[100], names[100], locations[100], cropData[100];
    int capacities[100];
    string u, oldName, oldLoc, data;
    int cap, count = 0;
    bool found = false;

    while (file >> u >> oldName >> oldLoc >> cap >> data)
    {
        if (count >= 100)
        {
            file.close();
            return false;
        }

        if (u == id)
        {
            oldName = name;
            oldLoc = loc;
            found = true;
        }

        ids[count] = u;
        names[count] = oldName;
        locations[count] = oldLoc;
        capacities[count] = cap;
        cropData[count] = data;
        count++;
    }

    file.close();

    if (!found)
        return false;

    ofstream output("mandi_details.txt");

    if (!output)
        return false;

    for (int i = 0; i < count; i++)
    {
        output << ids[i] << " "
               << names[i] << " "
               << locations[i] << " "
               << capacities[i] << " "
               << cropData[i] << "\n";
    }

    output.close();
    return true;
}

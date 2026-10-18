
#include "../include/farmer.h"
#include <iostream>
#include <fstream>

using namespace std;

Farmer::Farmer()
{
    farmerName = "";
    location = "";
}

Farmer::Farmer(string u, string p, string name, string loc)
    : User(u, p)
{
    farmerName = name;
    location = loc;
}

void Farmer::setFarmerName(string name)
{
    farmerName = name;
}

void Farmer::setLocation(string loc)
{
    location = loc;
}

string Farmer::getFarmerName()
{
    return farmerName;
}

string Farmer::getLocation()
{
    return location;
}

bool Farmer::addFarmer()
{
    string id = getUsername();
    string u, name, loc;

    if (id == "" || farmerName == "" || location == "")
        return false;

    ifstream check("farmer_details.txt");

    while (check >> u >> name >> loc)
    {
        if (u == id)
        {
            check.close();
            return false;
        }
    }
    check.close();

    ofstream file("farmer_details.txt", ios::app);

    if (!file)
        return false;

    file << id << " " << farmerName << " "
         << location << "\n";

    file.close();
    return true;
}

bool Farmer::viewFarmer(string id)
{
    ifstream file("farmer_details.txt");
    string u, name, loc;

    if (!file)
        return false;

    while (file >> u >> name >> loc)
    {
        if (u == id)
        {
            cout << "Farmer ID: " << u << endl;
            cout << "Name: " << name << endl;
            cout << "Location: " << loc << endl;

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool Farmer::updateFarmer(string id, string name, string loc)
{
    ifstream file("farmer_details.txt");

    if (!file)
        return false;

    string ids[100], names[100], locations[100];
    string u, oldName, oldLoc;
    int count = 0;
    bool found = false;

    while (file >> u >> oldName >> oldLoc)
    {
        if (u == id)
        {
            oldName = name;
            oldLoc = loc;
            found = true;
        }

        if (count == 100)
        {
            file.close();
            return false;
        }

        ids[count] = u;
        names[count] = oldName;
        locations[count] = oldLoc;
        count++;
    }

    file.close();

    if (!found)
        return false;

    ofstream output("farmer_details.txt");

    if (!output)
        return false;

    int i = 0;

    while (i < count)
    {
        output << ids[i] << " " << names[i] << " "
               << locations[i] << "\n";
        i++;
    }

    output.close();
    return true;
}


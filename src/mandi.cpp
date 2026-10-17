#include "../include/mandi.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Default constructor
Mandi::Mandi()
{
    mandiName = "";
    location = "";
    crops = {};
    capacity = 0;
}

// Parameterized constructor
Mandi::Mandi(string u, string p, string name, string loc,
             vector<string> crops, int capacity)
    : User(u, p)
{
    mandiName = name;
    location = loc;
    this->crops = crops;
    this->capacity = capacity;
}

// Setters
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

void Mandi::setCapacity(int c)
{
    capacity = c;
}

// Getters
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

int Mandi::getCapacity()
{
    return capacity;
}

// Add mandi
bool Mandi::addMandi()
{
    string id = getUsername();
    string u, name, loc, cropList;
    int cap;

    if (id == "" || mandiName == "" || location == "")
        return false;

    // Check for duplicate mandi
    ifstream check("mandi_details.txt");

    while (check >> u >> name >> loc >> cap >> cropList)
    {
        if (u == id)
        {
            check.close();
            return false;
        }
    }
    check.close();

    // Save mandi details
    ofstream file("mandi_details.txt", ios::app);

    if (!file)
        return false;

    file << id << " " << mandiName << " "
         << location << " " << capacity << " ";

    for (const string& crop : crops)
    {
        file << crop << ",";
    }

    file << "\n";
    file.close();

    return true;
}

// View mandi
bool Mandi::viewMandi(string id)
{
    ifstream file("mandi_details.txt");
    string u, name, loc, cropList;
    int cap;

    if (!file)
        return false;

    while (file >> u >> name >> loc >> cap >> cropList)
    {
        if (u == id)
        {
            cout << "Mandi Username: " << u << endl;
            cout << "Name: " << name << endl;
            cout << "Location: " << loc << endl;
            cout << "Capacity: " << cap << endl;
            cout << "Accepted Crops: " << cropList << endl;

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Search mandi
bool Mandi::searchMandi(string id)
{
    return viewMandi(id);
}

// Update mandi name and location
bool Mandi::updateMandi(string id, string name, string loc)
{
    ifstream file("mandi_details.txt");

    if (!file)
        return false;

    string ids[100], names[100], locations[100], cropLists[100];
    string u, oldName, oldLoc, cropList;
    int capacities[100];
    int cap;
    int count = 0;
    bool found = false;

    while (file >> u >> oldName >> oldLoc >> cap >> cropList)
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
        cropLists[count] = cropList;
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
               << cropLists[i] << "\n";
    }

    output.close();
    return true;
}
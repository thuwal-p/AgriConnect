#include "../include/mandi.h"
#include <iostream>
#include <fstream>
using namespace std;

Mandi::Mandi()
{
    mandiName = "";
    location = "";
}

Mandi::Mandi(string u, string p, string name, string loc)
    : User(u, p)
{
    mandiName = name;
    location = loc;
}

void Mandi::setMandiName(string name)
{
    mandiName = name;
}

void Mandi::setLocation(string loc)
{
    location = loc;
}

string Mandi::getMandiName()
{
    return mandiName;
}

string Mandi::getLocation()
{
    return location;
}

bool Mandi::addMandi()
{
    string id = getUsername();
    string u, name, loc;

    if (id == "" || mandiName == "" || location == "")
        return false;

    ifstream check("mandi_details.txt");

    while (check >> u >> name >> loc)
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
         << location << "\n";

    file.close();
    return true;
}

bool Mandi::viewMandi(string id)
{
    ifstream file("mandi_details.txt");
    string u, name, loc;

    if (!file)
        return false;

    while (file >> u >> name >> loc)
    {
        if (u == id)
        {
            cout << "Mandi ID: " << u << endl;
            cout << "Name: " << name << endl;
            cout << "Location: " << loc << endl;

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool Mandi::searchMandi(string id)
{
    return viewMandi(id);
}

bool Mandi::updateMandi(string id, string name, string loc)
{
    ifstream file("mandi_details.txt");

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

    ofstream output("mandi_details.txt");

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
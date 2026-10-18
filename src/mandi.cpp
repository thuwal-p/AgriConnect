
#include "../include/mandi.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Mandi::Mandi()
{
    mandiName = "";
    location = "";
    capacity = 0;
    crops.clear();
    buyingPrices.clear();
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
    string line;

    if (id.empty())
    {
        cout << "Invalid mandi username!" << endl;
        return false;
    }

    // Check whether details already exist.
    ifstream check("mandi_details.txt");

    while (getline(check, line))
    {
        istringstream row(line);

        string u, name, loc, cropData;
        int cap;

        if (!(row >> u >> name >> loc >> cap >> cropData))
        {
            continue;
        }

        if (u == id)
        {
            check.close();
            cout << "Mandi details already exist!" << endl;
            return false;
        }
    }

    check.close();

    int numberOfCrops;

    cout << "Enter Mandi Name: ";
    cin >> mandiName;

    cout << "Enter Location: ";
    cin >> location;

    cout << "Enter Mandi Capacity: ";

    if (!(cin >> capacity) || capacity <= 0)
    {
        cout << "Invalid capacity!" << endl;
        return false;
    }

    cout << "How many crops do you buy? ";

    if (!(cin >> numberOfCrops) || numberOfCrops <= 0)
    {
        cout << "Invalid number of crops!" << endl;
        return false;
    }

    crops.clear();
    buyingPrices.clear();

    for (int i = 0; i < numberOfCrops; i++)
    {
        string crop;
        double price;

        cout << "Enter crop name: ";
        cin >> crop;

        cout << "Enter buying price per kg: ";

        if (!(cin >> price) || price <= 0)
        {
            cout << "Invalid price!" << endl;
            return false;
        }

        crops.push_back(crop);
        buyingPrices.push_back(price);
    }

    ofstream file("mandi_details.txt", ios::app);

    if (!file)
    {
        cout << "Unable to open mandi details file!" << endl;
        return false;
    }

    file << id << " "
         << mandiName << " "
         << location << " "
         << capacity << " ";

    for (int i = 0; i < (int)crops.size(); i++)
    {
        file << crops[i] << ":" << buyingPrices[i];

        if (i < (int)crops.size() - 1)
        {
            file << ",";
        }
    }

    file << "\n";
    file.close();

    cout << "Mandi details added successfully!" << endl;
    return true;
}

bool Mandi::viewMandi(string id)
{
    ifstream file("mandi_details.txt");

    if (!file)
    {
        cout << "Unable to open mandi details file!" << endl;
        return false;
    }

    string line;

    while (getline(file, line))
    {
        istringstream row(line);

        string u, name, loc, cropData;
        int cap;

        if (!(row >> u >> name >> loc >> cap >> cropData))
        {
            continue;
        }

        if (u == id)
        {
            cout << "\n===== MY MANDI DETAILS =====" << endl;
            cout << "Username: " << u << endl;
            cout << "Mandi Name: " << name << endl;
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
                         << " - Rs. "
                         << item.substr(pos + 1)
                         << " per kg" << endl;
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
    {
        cout << "Unable to open mandi details file!" << endl;
        return false;
    }

    string ids[100];
    string names[100];
    string locations[100];
    string cropData[100];
    int capacities[100];

    string line;
    int count = 0;
    bool found = false;

    while (getline(file, line))
    {
        istringstream row(line);

        string u, oldName, oldLoc, data;
        int cap;

        if (!(row >> u >> oldName >> oldLoc >> cap >> data))
        {
            continue;
        }

        if (count >= 100)
        {
            file.close();
            cout << "Too many mandi records!" << endl;
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
    {
        return false;
    }

    ofstream output("mandi_details.txt");

    if (!output)
    {
        cout << "Unable to update mandi details file!" << endl;
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        output << ids[i] << " "
               << names[i] << " "
               << locations[i] << " "
               << capacities[i] << " "
               << cropData[i] << "\n";
    }

    output.close();

    cout << "Mandi details updated successfully!" << endl;
    return true;
}


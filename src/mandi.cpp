
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
    int numberOfCrops;

    if (id == "")
    {
        cout << "Invalid mandi username!" << endl;
        return false;
    }

    // Check if mandi details already exist
    ifstream check("mandi_details.txt");

    while (check >> u >> name >> loc >> cap >> cropData)
    {
        if (u == id)
        {
            check.close();
            cout << "Mandi details already exist!" << endl;
            return false;
        }
    }

    check.close();

    cout << "\nEnter Mandi Name: ";
    cin >> mandiName;

    cout << "Enter Location: ";
    cin >> location;

    cout << "Enter Mandi Capacity: ";

    if (!(cin >> capacity))
    {
        cout << "Invalid capacity!" << endl;
        cin.clear();
        return false;
    }

    if (capacity <= 0)
    {
        cout << "Capacity must be greater than zero!" << endl;
        return false;
    }

    cout << "How many crops do you want to buy? ";

    if (!(cin >> numberOfCrops))
    {
        cout << "Invalid number of crops!" << endl;
        cin.clear();
        return false;
    }

    if (numberOfCrops <= 0)
    {
        cout << "Number of crops must be greater than zero!" << endl;
        return false;
    }

    crops.clear();
    buyingPrices.clear();

    for (int i = 0; i < numberOfCrops; i++)
    {
        string crop;
        double price;

        cout << "\nEnter crop " << i + 1 << " name: ";
        cin >> crop;

        cout << "Enter buying price per kg for "
             << crop << ": Rs. ";

        if (!(cin >> price))
        {
            cout << "Invalid buying price!" << endl;
            cin.clear();
            return false;
        }

        if (price <= 0)
        {
            cout << "Price must be greater than zero!" << endl;
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

    cout << "\nMandi details added successfully!" << endl;

    return true;
}

bool Mandi::viewMandi(string id)
{
    ifstream file("mandi_details.txt");

    string u, name, loc, cropData;
    int cap;

    if (!file)
    {
        return false;
    }

    while (file >> u >> name >> loc >> cap >> cropData)
    {
        if (u == id)
        {
            cout << "\nMandi Username: " << u << endl;
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
        return false;
    }

    string ids[100], names[100], locations[100], cropData[100];
    int capacities[100];

    string u, oldName, oldLoc, data;
    int cap;
    int count = 0;
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
    {
        return false;
    }

    ofstream output("mandi_details.txt");

    if (!output)
    {
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

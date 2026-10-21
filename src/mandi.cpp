
#include "../include/mandi.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// DEFAULT CONSTRUCTOR
Mandi::Mandi()
{
    mandiName = "";
    location = "";
    capacity = 0;
    crops.clear();
    buyingPrices.clear();
}

// PARAMETERIZED CONSTRUCTOR
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

// SETTERS
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

// GETTERS
string Mandi::getMandiName()
{
    return mandiName;
}

string Mandi::getLocation()
{
    return location;
}

vector<string> Mandi::getCrops() const
{
    return crops;
}

vector<double> Mandi::getBuyingPrices() const
{
    return buyingPrices;
}

int Mandi::getCapacity()
{
    return capacity;
}

// ADD MANDI DETAILS
bool Mandi::addMandi()
{
    string id = getUsername();
    string line;

    if (id.empty())
    {
        cout << "Invalid mandi username!\n";
        return false;
    }

    ifstream check("mandi_details.txt");

    if (check)
    {
        while (getline(check, line))
        {
            istringstream row(line);

            string u;

            if (row >> u && u == id)
            {
                check.close();
                cout << "Mandi details already exist!\n";
                return false;
            }
        }

        check.close();
    }

    int numberOfCrops;

    cout << "Enter Mandi Name (one word): ";
    cin >> mandiName;

    cout << "Enter Location (one word): ";
    cin >> location;

    cout << "Enter Mandi Capacity: ";

    if (!(cin >> capacity) || capacity <= 0)
    {
        cout << "Invalid capacity!\n";
        return false;
    }

    cout << "How many crops do you buy? ";

    if (!(cin >> numberOfCrops) || numberOfCrops <= 0)
    {
        cout << "Invalid number of crops!\n";
        return false;
    }

    crops.clear();
    buyingPrices.clear();

    for (int i = 0; i < numberOfCrops; i++)
    {
        string crop;
        double price;

        cout << "Enter crop " << i + 1 << " name: ";
        cin >> crop;

        cout << "Enter buying price per kg: ";

        if (!(cin >> price) || price <= 0)
        {
            cout << "Invalid price!\n";
            return false;
        }

        crops.push_back(crop);
        buyingPrices.push_back(price);
    }

    ofstream output("mandi_details.txt", ios::app);

    if (!output)
    {
        cout << "Unable to open mandi details file!\n";
        return false;
    }

    output << id << " " << mandiName << " "
           << location << " " << capacity << " ";

    for (int i = 0; i < (int)crops.size(); i++)
    {
        if (i > 0)
            output << ",";

        output << crops[i] << ":" << buyingPrices[i];
    }

    output << "\n";
    output.close();

    cout << "Mandi details added successfully!\n";
    return true;
}

// VIEW MANDI DETAILS
bool Mandi::viewMandi(string id)
{
    ifstream file("mandi_details.txt");

    if (!file)
    {
        cout << "Unable to open mandi details file!\n";
        return false;
    }

    string line;

    while (getline(file, line))
    {
        istringstream row(line);

        string u, name, loc, data;
        int cap;

        if (!(row >> u >> name >> loc >> cap))
            continue;

        getline(row, data);

        // Remove leading spaces from crop data.
        size_t start = data.find_first_not_of(" \t");

        if (start == string::npos)
            data = "";
        else
            data = data.substr(start);

        if (u == id)
        {
            cout << "\n===== MY MANDI DETAILS =====\n";
            cout << "Username: " << u << "\n";
            cout << "Mandi Name: " << name << "\n";
            cout << "Location: " << loc << "\n";
            cout << "Capacity: " << cap << "\n";
            cout << "Crop Buying Prices:\n";

            if (data.empty())
            {
                cout << "No crop listings available.\n";
            }
            else
            {
                stringstream ss(data);
                string item;

                while (getline(ss, item, ','))
                {
                    size_t pos = item.find(':');

                    if (pos != string::npos)
                    {
                        cout << item.substr(0, pos)
                             << " - Rs. "
                             << item.substr(pos + 1)
                             << " per kg\n";
                    }
                }
            }

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

vector<Mandi> Mandi::getAllMandis()
{
    vector<Mandi> allMandis;

    ifstream file("mandi_details.txt");

    if (!file.is_open())
    {
        return allMandis;
    }

    string id, name, loc, cropData;
    int capacity;

    while (file >> id >> name >> loc >> capacity >> cropData)
    {
        vector<string> crops;
        vector<double> prices;

        stringstream ss(cropData);
        string cropPrice;

        while (getline(ss, cropPrice, ','))
        {
            size_t colon = cropPrice.find(':');

            if (colon != string::npos)
            {
                string crop = cropPrice.substr(0, colon);
                double price = stod(cropPrice.substr(colon + 1));

                crops.push_back(crop);
                prices.push_back(price);
            }
        }

        Mandi mandi(id, "", name, loc, crops, prices, capacity);

        allMandis.push_back(mandi);
    }

    file.close();

    return allMandis;
}

// UPDATE MANDI DETAILS
bool Mandi::updateMandi(string id)
{
    ifstream file("mandi_details.txt");

    if (!file)
    {
        cout << "Unable to open mandi details file!\n";
        return false;
    }

    string ids[100];
    string names[100];
    string locations[100];
    string data[100];
    int capacities[100];

    string line;
    int count = 0;
    int recordIndex = -1;

    while (getline(file, line))
    {
        istringstream row(line);

        string u, name, loc, cropData;
        int cap;

        if (!(row >> u >> name >> loc >> cap))
            continue;

        getline(row, cropData);

        size_t start = cropData.find_first_not_of(" \t");

        if (start == string::npos)
            cropData = "";
        else
            cropData = cropData.substr(start);

        if (count >= 100)
        {
            file.close();
            cout << "Too many mandi records!\n";
            return false;
        }

        ids[count] = u;
        names[count] = name;
        locations[count] = loc;
        capacities[count] = cap;
        data[count] = cropData;

        if (u == id && recordIndex == -1)
            recordIndex = count;

        count++;
    }

    file.close();

    if (recordIndex == -1)
    {
        cout << "Mandi details not found. Add them first.\n";
        return false;
    }

    int r = recordIndex;

    cout << "\n===== UPDATE MANDI DETAILS =====\n";

    cout << "Current name: " << names[r] << "\n";
    cout << "Enter new name (one word): ";
    cin >> names[r];

    cout << "Current location: " << locations[r] << "\n";
    cout << "Enter new location (one word): ";
    cin >> locations[r];

    cout << "Current capacity: " << capacities[r] << "\n";
    cout << "Enter new capacity: ";

    if (!(cin >> capacities[r]) || capacities[r] <= 0)
    {
        cout << "Invalid capacity!\n";
        return false;
    }

    string cropNames[100];
    string cropPrices[100];
    int cropCount = 0;

    stringstream ss(data[r]);
    string item;

    while (getline(ss, item, ',') && cropCount < 100)
    {
        size_t pos = item.find(':');

        if (pos != string::npos)
        {
            cropNames[cropCount] = item.substr(0, pos);
            cropPrices[cropCount] = item.substr(pos + 1);
            cropCount++;
        }
    }

    if (cropCount > 0)
    {
        cout << "\n===== EXISTING CROP LISTINGS =====\n";

        for (int i = 0; i < cropCount; i++)
        {
            cout << i + 1 << ". "
                 << cropNames[i]
                 << " - Rs. " << cropPrices[i]
                 << " per kg\n";
        }

        int choice;

        cout << "\nUpdate a crop listing?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid choice!\n";
            return false;
        }

        if (choice == 1)
        {
            int cropChoice;

            cout << "Enter crop number to update: ";

            if (!(cin >> cropChoice) ||
                cropChoice < 1 || cropChoice > cropCount)
            {
                cout << "Invalid crop number!\n";
                return false;
            }

            string newCrop;
            double newPrice;

            cout << "Enter new crop name (one word): ";
            cin >> newCrop;

            cout << "Enter new buying price per kg: ";

            if (!(cin >> newPrice) || newPrice <= 0)
            {
                cout << "Invalid price!\n";
                return false;
            }

            cropNames[cropChoice - 1] = newCrop;

            stringstream priceStream;
            priceStream << newPrice;

            cropPrices[cropChoice - 1] = priceStream.str();
        }
        else if (choice != 2)
        {
            cout << "Invalid choice!\n";
            return false;
        }
    }
    else
    {
        cout << "No existing crop listings found.\n";
    }

    stringstream newData;

    for (int i = 0; i < cropCount; i++)
    {
        if (i > 0)
            newData << ",";

        newData << cropNames[i]
                << ":" << cropPrices[i];
    }

    data[r] = newData.str();

    ofstream output("mandi_details.txt");

    if (!output)
    {
        cout << "Unable to save mandi details!\n";
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        output << ids[i] << " "
               << names[i] << " "
               << locations[i] << " "
               << capacities[i] << " "
               << data[i] << "\n";
    }

    output.close();

    cout << "Mandi details updated successfully!\n";
    return true;
}

bool Mandi::updateMandiCapacity(string id, int newCapacity)
{
    ifstream file("mandi_details.txt");

    if (!file.is_open())
    {
        return false;
    }

    vector<string> records;
    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string mandiID;
        string name;
        string location;
        int capacity;
        string cropData;

        ss >> mandiID >> name >> location >> capacity >> cropData;

        if (mandiID == id)
        {
            capacity = newCapacity;
            found = true;

            string updatedLine =
                mandiID + " " +
                name + " " +
                location + " " +
                to_string(capacity) + " " +
                cropData;

            records.push_back(updatedLine);
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    if (!found)
    {
        return false;
    }

    ofstream outFile("mandi_details.txt");

    if (!outFile.is_open())
    {
        return false;
    }

    for (string record : records)
    {
        outFile << record << endl;
    }

    outFile.close();

    return true;
}

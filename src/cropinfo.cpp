
#include "../include/cropinfo.h"
#include <iostream>
#include <fstream>
using namespace std;

CropInfo::CropInfo()
{
    farmerID = "";
    cropName = "";
    quantity = 0;
}

CropInfo::CropInfo(string id, string crop, int qty)
{
    farmerID = id;
    cropName = crop;
    quantity = qty;
}

void CropInfo::setCropName(string crop)
{
    cropName = crop;
}

void CropInfo::setQuantity(int qty)
{
    quantity = qty;
}

string CropInfo::getFarmerID()
{
    return farmerID;
}

string CropInfo::getCropName()
{
    return cropName;
}

int CropInfo::getQuantity()
{
    return quantity;
}

// ADD CROP
bool CropInfo::addCrop()
{
    if (farmerID.empty() || cropName.empty())
    {
        cout << "Error: Farmer ID and crop name cannot be empty.\n";
        return false;
    }

    if (quantity <= 0)
    {
        cout << "Error: Quantity must be greater than zero.\n";
        return false;
    }

    if (cropName.find(' ') != string::npos)
    {
        cout << "Error: Enter the crop name as one word.\n";
        return false;
    }

    ifstream checkFile("crops.txt");
    string farmer, crop;
    int qty;

    while (checkFile >> farmer >> crop >> qty)
    {
        if (farmer == farmerID && crop == cropName)
        {
            checkFile.close();
            cout << "Error: You have already listed this crop.\n";
            return false;
        }
    }
    checkFile.close();

    ofstream file("crops.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Error: Unable to open crops.txt for writing.\n";
        return false;
    }

    file << farmerID << " " << cropName << " "
         << quantity << "\n";

    file.close();

    cout << "Crop added successfully.\n";
    return true;
}

// VIEW FARMER'S CROPS
void CropInfo::viewMyCrops(string id)
{
    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "No crop listings found yet.\n";
        return;
    }

    string farmer, crop;
    int qty;
    bool found = false;

    while (file >> farmer >> crop >> qty)
    {
        if (farmer == id)
        {
            //cout << "Farmer ID: " << farmer << endl;
            cout << "Crop Name: " << crop << endl;
            cout << "Quantity: " << qty << " kg\n";
            cout << "----------------------\n";
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "You have not listed any crops yet.\n";
}

vector<CropInfo> CropInfo::getMyCrops(string id)
{
    vector<CropInfo> myCrops;

    ifstream file("crops.txt");

    if (!file.is_open())
    {
        return myCrops;
    }

    string farmer, crop;
    int qty;

    while (file >> farmer >> crop >> qty)
    {
        if (farmer == id)
        {
            CropInfo c(farmer, crop, qty);
            myCrops.push_back(c);
        }
    }

    file.close();

    return myCrops;
}

// UPDATE CROP
bool CropInfo::updateCrop(string id, string target, int qty)
{
    if (id.empty() || target.empty() || qty <= 0)
    {
        cout << "Error: Enter a valid crop name and quantity.\n";
        return false;
    }

    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "Error: No crop file exists to update.\n";
        return false;
    }

    string ids[500], cropNames[500], farmer, crop;
    int quantities[500], oldQty;
    int count = 0;
    bool found = false;

    while (file >> farmer >> crop >> oldQty)
    {
        if (count >= 500)
        {
            file.close();
            cout << "Error: Crop record limit exceeded.\n";
            return false;
        }

        ids[count] = farmer;
        cropNames[count] = crop;
        quantities[count] = oldQty;

        if (farmer == id && crop == target && !found)
        {
            quantities[count] = qty;
            found = true;
        }

        count++;
    }

    file.close();

    if (!found)
    {
        cout << "Error: Crop not found for this farmer.\n";
        return false;
    }

    ofstream output("crops.txt");

    if (!output.is_open())
        return false;

    int i = 0;
    while (i < count)
    {
        output << ids[i] << " " << cropNames[i] << " "
               << quantities[i] << "\n";
        i++;
    }

    output.close();

    cout << "Crop updated successfully.\n";
    return true;
}

// REMOVE CROP
bool CropInfo::removeCrop(string id, string target)
{
    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "Error: No crop file exists.\n";
        return false;
    }

    string ids[500], cropNames[500], farmer, crop;
    int quantities[500], qty;
    int count = 0;
    bool removed = false;

    while (file >> farmer >> crop >> qty)
    {
        if (farmer == id && crop == target && !removed)
        {
            removed = true;
            continue;
        }

        if (count >= 500)
        {
            file.close();
            return false;
        }

        ids[count] = farmer;
        cropNames[count] = crop;
        quantities[count] = qty;
        count++;
    }

    file.close();

    if (!removed)
    {
        cout << "Error: Crop not found for this farmer.\n";
        return false;
    }

    ofstream output("crops.txt");

    if (!output.is_open())
        return false;

    int i = 0;
    while (i < count)
    {
        output << ids[i] << " " << cropNames[i] << " "
               << quantities[i] << "\n";
        i++;
    }

    output.close();

    cout << "Crop removed successfully.\n";
    return true;
}


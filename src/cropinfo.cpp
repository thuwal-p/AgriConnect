
#include "../include/cropinfo.h"
#include <iostream>
#include <fstream>
using namespace std;

CropInfo::CropInfo()
{
    farmerID = "";
    cropName = "";
    quantity = 0;
    expectedPrice = 0;
}

CropInfo::CropInfo(string id, string crop, int qty, double price)
{
    farmerID = id;
    cropName = crop;
    quantity = qty;
    expectedPrice = price;
}

void CropInfo::setCropName(string crop)
{
    cropName = crop;
}

void CropInfo::setQuantity(int qty)
{
    quantity = qty;
}

void CropInfo::setExpectedPrice(double price)
{
    expectedPrice = price;
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

double CropInfo::getExpectedPrice()
{
    return expectedPrice;
}

// ADD CROP
bool CropInfo::addCrop()
{
    if (farmerID.empty() || cropName.empty())
    {
        cout << "Error: Farmer ID and crop name cannot be empty.\n";
        return false;
    }

    if (quantity <= 0 || expectedPrice <= 0)
    {
        cout << "Error: Quantity and price must be greater than zero.\n";
        return false;
    }

    if (cropName.find(' ') != string::npos)
    {
        cout << "Error: Enter the crop name as one word.\n";
        return false;
    }

    ifstream checkFile("crops.txt");

    if (checkFile.is_open())
    {
        string farmer, crop;
        int qty;
        double price;

        while (checkFile >> farmer >> crop >> qty >> price)
        {
            if (farmer == farmerID && crop == cropName)
            {
                checkFile.close();
                cout << "Error: You have already listed this crop.\n";
                return false;
            }
        }

        if (!checkFile.eof())
        {
            checkFile.close();
            cout << "Error: Crop file contains invalid data.\n";
            return false;
        }

        checkFile.close();
    }
    else
    {
        // Check whether the file exists but cannot be read.
        ifstream testFile("crops.txt");

        if (testFile.fail())
        {
            // A missing file is acceptable for the first listing.
            // The append operation below will attempt to create it.
            testFile.close();
        }
    }

    ofstream file("crops.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Error: Unable to open crops.txt for writing.\n";
        return false;
    }

    file << farmerID << " " << cropName << " "
         << quantity << " " << expectedPrice << "\n";

    if (!file)
    {
        cout << "Error: Could not save the crop listing.\n";
        file.close();
        return false;
    }

    file.close();

    cout << "Crop added successfully.\n";
    return true;
}

// VIEW FARMER'S CROPS
void CropInfo::viewMyCrops(string id)
{
    if (id.empty())
    {
        cout << "Error: Farmer ID cannot be empty.\n";
        return;
    }

    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "No crop listings found yet.\n";
        return;
    }

    string farmer, crop;
    int qty;
    double price;
    bool found = false;

    while (file >> farmer >> crop >> qty >> price)
    {
        if (farmer == id)
        {
            cout << "\nFarmer ID: " << farmer << endl;
            cout << "Crop: " << crop << endl;
            cout << "Quantity: " << qty << " kg\n";
            cout << "Expected price: Rs. " << price
                 << " per kg\n";
            cout << "----------------------\n";
            found = true;
        }
    }

    if (!file.eof())
    {
        cout << "Error: Invalid data found in crops.txt.\n";
    }

    file.close();

    if (!found)
    {
        cout << "You have not listed any crops yet.\n";
    }
}

// VIEW ALL CROPS FOR MANDI
void CropInfo::viewAllCrops()
{
    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "No crop listings found yet.\n";
        return;
    }

    string farmer, crop;
    int qty;
    double price;
    bool found = false;

    cout << "\n===== AVAILABLE CROPS =====\n";

    while (file >> farmer >> crop >> qty >> price)
    {
        cout << "\nFarmer ID: " << farmer << endl;
        cout << "Crop: " << crop << endl;
        cout << "Quantity: " << qty << " kg\n";
        cout << "Expected price: Rs. " << price
             << " per kg\n";
        cout << "----------------------\n";
        found = true;
    }

    if (!file.eof())
    {
        cout << "Error: Invalid data found in crops.txt.\n";
    }

    file.close();

    if (!found)
    {
        cout << "No crops are available for sale.\n";
    }
}

// SEARCH CROP
bool CropInfo::searchCrop(string target)
{
    if (target.empty())
    {
        cout << "Error: Search name cannot be empty.\n";
        return false;
    }

    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "No crop listings found yet.\n";
        return false;
    }

    string farmer, crop;
    int qty;
    double price;
    bool found = false;

    while (file >> farmer >> crop >> qty >> price)
    {
        if (crop == target)
        {
            cout << "\nFarmer ID: " << farmer << endl;
            cout << "Crop: " << crop << endl;
            cout << "Quantity: " << qty << " kg\n";
            cout << "Expected price: Rs. " << price
                 << " per kg\n";
            cout << "----------------------\n";
            found = true;
        }
    }

    if (!file.eof())
    {
        cout << "Error: Invalid data found in crops.txt.\n";
        file.close();
        return false;
    }

    file.close();

    if (!found)
    {
        cout << "No matching crop found.\n";
    }

    return found;
}

// UPDATE CROP
bool CropInfo::updateCrop(string id, string target,
                          int qty, double price)
{
    if (id.empty() || target.empty())
    {
        cout << "Error: Farmer ID and crop name cannot be empty.\n";
        return false;
    }

    if (qty <= 0 || price <= 0)
    {
        cout << "Error: Quantity and price must be positive.\n";
        return false;
    }

    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "Error: No crop file exists to update.\n";
        return false;
    }

    string ids[500], crops[500], farmer, crop;
    int quantities[500], oldQty;
    double prices[500], oldPrice;
    int count = 0;
    bool found = false;

    while (file >> farmer >> crop >> oldQty >> oldPrice)
    {
        if (count >= 500)
        {
            file.close();
            cout << "Error: Crop record limit exceeded.\n";
            return false;
        }

        ids[count] = farmer;
        crops[count] = crop;
        quantities[count] = oldQty;
        prices[count] = oldPrice;

        if (farmer == id && crop == target && !found)
        {
            quantities[count] = qty;
            prices[count] = price;
            found = true;
        }

        count++;
    }

    if (!file.eof())
    {
        file.close();
        cout << "Error: Invalid data in crops.txt. Nothing updated.\n";
        return false;
    }

    file.close();

    if (!found)
    {
        cout << "Error: Crop not found for this farmer.\n";
        return false;
    }

    ofstream output("crops.txt");

    if (!output.is_open())
    {
        cout << "Error: Unable to save updated records.\n";
        return false;
    }

    int i = 0;

    while (i < count)
    {
        output << ids[i] << " " << crops[i] << " "
               << quantities[i] << " " << prices[i] << "\n";

        if (!output)
        {
            output.close();
            cout << "Error: Failed while writing crop records.\n";
            return false;
        }

        i++;
    }

    output.close();

    cout << "Crop updated successfully.\n";
    return true;
}

// REMOVE CROP
bool CropInfo::removeCrop(string id, string target)
{
    if (id.empty() || target.empty())
    {
        cout << "Error: Farmer ID and crop name cannot be empty.\n";
        return false;
    }

    ifstream file("crops.txt");

    if (!file.is_open())
    {
        cout << "Error: No crop file exists to update.\n";
        return false;
    }

    string ids[500], crops[500], farmer, crop;
    int quantities[500], qty;
    double prices[500], price;
    int count = 0;
    bool removed = false;

    while (file >> farmer >> crop >> qty >> price)
    {
        if (farmer == id && crop == target && !removed)
        {
            removed = true;
            continue;
        }

        if (count >= 500)
        {
            file.close();
            cout << "Error: Crop record limit exceeded.\n";
            return false;
        }

        ids[count] = farmer;
        crops[count] = crop;
        quantities[count] = qty;
        prices[count] = price;
        count++;
    }

    if (!file.eof())
    {
        file.close();
        cout << "Error: Invalid data in crops.txt. Nothing removed.\n";
        return false;
    }

    file.close();

    if (!removed)
    {
        cout << "Error: Crop not found for this farmer.\n";
        return false;
    }

    ofstream output("crops.txt");

    if (!output.is_open())
    {
        cout << "Error: Unable to save crop records.\n";
        return false;
    }

    int i = 0;

    while (i < count)
    {
        output << ids[i] << " " << crops[i] << " "
               << quantities[i] << " " << prices[i] << "\n";

        if (!output)
        {
            output.close();
            cout << "Error: Failed while writing crop records.\n";
            return false;
        }

        i++;
    }

    output.close();

    cout << "Crop removed successfully.\n";
    return true;
}

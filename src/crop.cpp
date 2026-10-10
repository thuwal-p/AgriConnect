
#include "crop.h"
#include <iostream>
using namespace std;

// Default constructor
Crop::Crop()
{
    cropId = 0;
    cropName = "";
    quantity = 0;
    category = "";
}

// Parameterized constructor
Crop::Crop(int id, string name, float qty, string cat)
{
    cropId = id;
    cropName = name;
    quantity = qty;
    category = cat;
}

// Add crop details
void Crop::addCrop()
{
    cout << "Enter Crop ID: ";
    cin >> cropId;

    cout << "Enter Crop Name: ";
    cin >> cropName;

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Category: ";
    cin >> category;

    cout << "Crop added successfully!\n";
}

// View crop details
void Crop::viewCrop()
{
    cout << "\nCrop ID: " << cropId;
    cout << "\nCrop Name: " << cropName;
    cout << "\nQuantity: " << quantity;
    cout << "\nCategory: " << category << endl;
}

// Update crop details
void Crop::updateCrop()
{
    cout << "Enter new Crop Name: ";
    cin >> cropName;

    cout << "Enter new Quantity: ";
    cin >> quantity;

    cout << "Enter new Category: ";
    cin >> category;

    cout << "Crop updated successfully!\n";
}

// Getter functions
int Crop::getCropId()
{
    return cropId;
}

string Crop::getCropName()
{
    return cropName;
}

float Crop::getQuantity()
{
    return quantity;
}

string Crop::getCategory()
{
    return category;
}

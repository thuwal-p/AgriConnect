
#include "include/user.h"
#include "include/farmer.h"
#include "include/mandi.h"
#include "include/cropinfo.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool hasSpace(string text)
{
    int i = 0;

    while (i < text.length())
    {
        if (text[i] == ' ' || text[i] == '\t')
            return true;

        i++;
    }

    return false;
}

bool readInteger(int &value)
{
    if (!(cin >> value))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a whole number.\n";
        return false;
    }

    cin.ignore(1000, '\n');
    return true;
}

bool readPrice(double &price)
{
    if (!(cin >> price))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid price.\n";
        return false;
    }

    cin.ignore(1000, '\n');

    if (price <= 0)
    {
        cout << "Price must be greater than zero.\n";
        return false;
    }

    return true;
}

// FARMER MENU
void farmerMenu(string username)
{
    Farmer farmer(username, "", "", "");
    CropInfo crop;

    int choice, quantity;
    double price;
    string id, name, location, cropName;

    while (true)
    {
        cout << "\n===== FARMER MENU =====\n";
        cout << "1. Add Farmer Details\n";
        cout << "2. View My Farmer Details\n";
        cout << "3. Search Farmer\n";
        cout << "4. Update Farmer Details\n";
        cout << "5. Add Crop for Sale\n";
        cout << "6. View My Crops\n";
        cout << "7. Update My Crop Listing\n";
        cout << "8. Remove My Crop Listing\n";
        cout << "9. Logout\n";
        cout << "Enter choice: ";

        if (!readInteger(choice))
            continue;

        if (choice == 1)
        {
            cout << "Enter farmer name (one word): ";
            getline(cin, name);

            cout << "Enter location (one word): ";
            getline(cin, location);

            if (name.empty() || location.empty() ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Enter valid single-word name and location.\n";
            }
            else
            {
                farmer.setFarmerName(name);
                farmer.setLocation(location);

                if (farmer.addFarmer())
                    cout << "Farmer details added successfully.\n";
                else
                    cout << "Could not add details. They may already exist.\n";
            }
        }
        else if (choice == 2)
        {
            if (!farmer.viewFarmer(username))
                cout << "Farmer details not found. Add them first.\n";
        }
        else if (choice == 3)
        {
            cout << "Enter farmer ID to search: ";
            getline(cin, id);

            if (!farmer.searchFarmer(id))
                cout << "Farmer not found.\n";
        }
        else if (choice == 4)
        {
            cout << "Enter farmer ID to update: ";
            getline(cin, id);

            cout << "Enter new name (one word): ";
            getline(cin, name);

            cout << "Enter new location (one word): ";
            getline(cin, location);

            if (id.empty() || name.empty() || location.empty() ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Enter valid details.\n";
            }
            else if (farmer.updateFarmer(id, name, location))
            {
                cout << "Farmer details updated successfully.\n";
            }
            else
            {
                cout << "Farmer not found or update failed.\n";
            }
        }
        else if (choice == 5)
        {
            cout << "Enter crop name (one word): ";
            getline(cin, cropName);

            if (cropName.empty() || hasSpace(cropName))
            {
                cout << "Enter a valid single-word crop name.\n";
                continue;
            }

            cout << "Enter quantity in kg: ";
            if (!readInteger(quantity))
                continue;

            if (quantity <= 0)
            {
                cout << "Quantity must be greater than zero.\n";
                continue;
            }

            cout << "Enter expected price per kg: ";
            if (!readPrice(price))
                continue;

            CropInfo newCrop(username, cropName, quantity, price);
            newCrop.addCrop();
        }
        else if (choice == 6)
        {
            crop.viewMyCrops(username);
        }
        else if (choice == 7)
        {
            cout << "Enter crop name to update: ";
            getline(cin, cropName);

            if (cropName.empty() || hasSpace(cropName))
            {
                cout << "Enter a valid single-word crop name.\n";
                continue;
            }

            cout << "Enter new quantity in kg: ";
            if (!readInteger(quantity))
                continue;

            if (quantity <= 0)
            {
                cout << "Quantity must be greater than zero.\n";
                continue;
            }

            cout << "Enter new expected price per kg: ";
            if (!readPrice(price))
                continue;

            crop.updateCrop(username, cropName, quantity, price);
        }
        else if (choice == 8)
        {
            cout << "Enter crop name to remove: ";
            getline(cin, cropName);

            if (cropName.empty() || hasSpace(cropName))
                cout << "Enter a valid single-word crop name.\n";
            else
                crop.removeCrop(username, cropName);
        }
        else if (choice == 9)
        {
            cout << "Logged out successfully.\n";
            return;
        }
        else
        {
            cout << "Invalid choice. Select 1 to 9.\n";
        }
    }
}

// MANDI MENU
void mandiMenu(string username)
{
    Mandi mandi(username, "", "", "", vector<string>(),
                vector<double>(), 0);

    CropInfo crop;

    int choice;
    string id, name, location;

    while (true)
    {
        cout << "\n===== MANDI MENU =====\n";
        cout << "1. Add Mandi Details\n";
        cout << "2. View My Mandi Details\n";
        cout << "3. Update Mandi Details\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";

        if (!readInteger(choice))
            continue;

        if (choice == 1)
        {
            int capacity, cropCount;
            vector<string> crops;
            vector<double> buyingPrices;
            string cropName;
            double buyingPrice;

            cout << "Enter mandi name (one word): ";
            getline(cin, name);

            cout << "Enter location (one word): ";
            getline(cin, location);

            if (name.empty() || location.empty() ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Enter valid single-word name and location.\n";
                continue;
            }

            cout << "Enter storage capacity: ";
            if (!readInteger(capacity) || capacity <= 0)
            {
                cout << "Capacity must be a positive whole number.\n";
                continue;
            }

            cout << "Enter number of crops the mandi buys: ";
            if (!readInteger(cropCount) || cropCount <= 0)
            {
                cout << "Enter a positive number of crops.\n";
                continue;
            }

            bool valid = true;
            int i = 0;

            while (i < cropCount)
            {
                cout << "Enter crop name (one word): ";
                getline(cin, cropName);

                if (cropName.empty() || hasSpace(cropName))
                {
                    cout << "Enter a valid single-word crop name.\n";
                    valid = false;
                    break;
                }

                cout << "Enter buying price per kg: ";
                if (!readPrice(buyingPrice))
                {
                    valid = false;
                    break;
                }

                crops.push_back(cropName);
                buyingPrices.push_back(buyingPrice);
                i++;
            }

            if (!valid)
                continue;

            Mandi newMandi(username, "", name, location,
                           crops, buyingPrices, capacity);

            if (newMandi.addMandi())
                cout << "Mandi details and crop buying prices added successfully.\n";
            else
                cout << "Could not add details. They may already exist.\n";
        }
        else if (choice == 2)
        {
            if (!mandi.viewMandi(username))
                cout << "Mandi details not found. Add them first.\n";
        }
        else if (choice == 3)
        {
            cout << "Enter mandi ID to update: ";
            getline(cin, id);

            cout << "Enter new name (one word): ";
            getline(cin, name);

            cout << "Enter new location (one word): ";
            getline(cin, location);

            if (id.empty() || name.empty() || location.empty() ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Enter valid details.\n";
            }
            else if (mandi.updateMandi(id, name, location))
            {
                cout << "Mandi details updated successfully.\n";
            }
            else
            {
                cout << "Mandi not found or update failed.\n";
            }
        }
        else if (choice == 4)
        {
            cout << "Logged out successfully.\n";
            return;
        }
        else
        {
            cout << "Invalid choice. Select 1 to 4.\n";
        }
    }
}

// MAIN FUNCTION
int main()
{
    UserAuthentication auth;

    auth.loadFarmers();
    auth.loadMandis();

    int choice, attempts;
    string username, password;

    while (true)
    {
        cout << "\n===== AGRICONNECT =====\n";
        cout << "1. Farmer Login\n";
        cout << "2. Farmer Registration\n";
        cout << "3. Mandi Login\n";
        cout << "4. Mandi Registration\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!readInteger(choice))
            continue;

        if (choice == 1 || choice == 3)
        {
            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            if (username.empty() || password.empty() ||
                hasSpace(username) || hasSpace(password))
            {
                cout << "Enter a valid username and password without spaces.\n";
                continue;
            }

            if (choice == 1 && !auth.farmerUsernameExists(username))
            {
                cout << "Farmer username not found. Register first.\n";
                continue;
            }

            if (choice == 3 && !auth.mandiUsernameExists(username))
            {
                cout << "Mandi username not found. Register first.\n";
                continue;
            }

            attempts = 3;
            bool loggedIn = false;

            while (attempts > 0)
            {
                if (choice == 1)
                    loggedIn = auth.farmerLogin(username, password);
                else
                    loggedIn = auth.mandiLogin(username, password);

                if (loggedIn)
                    break;

                attempts--;

                if (attempts > 0)
                {
                    cout << "Incorrect password. Attempts left: "
                         << attempts << "\n";
                    cout << "Enter password again: ";
                    getline(cin, password);
                }
                else
                {
                    cout << "Too many incorrect attempts.\n";
                }
            }

            if (loggedIn)
            {
                if (choice == 1)
                {
                    cout << "Farmer login successful.\n";
                    farmerMenu(username);
                }
                else
                {
                    cout << "Mandi login successful.\n";
                    mandiMenu(username);
                }
            }
        }
        else if (choice == 2 || choice == 4)
        {
            cout << "Choose username: ";
            getline(cin, username);

            cout << "Choose password: ";
            getline(cin, password);

            if (username.empty() || password.empty() ||
                hasSpace(username) || hasSpace(password))
            {
                cout << "Username and password must be non-empty and contain no spaces.\n";
                continue;
            }

            if (choice == 2)
            {
                if (auth.registerFarmer(username, password))
                {
                    cout << "Farmer registration successful.\n";
                    farmerMenu(username);
                }
                else
                {
                    cout << "Username already exists or registration failed.\n";
                }
            }
            else
            {
                if (auth.registerMandi(username, password))
                {
                    cout << "Mandi registration successful.\n";
                    mandiMenu(username);
                }
                else
                {
                    cout << "Username already exists or registration failed.\n";
                }
            }
        }
        else if (choice == 5)
        {
            cout << "Thank you for using AgriConnect!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Select 1 to 5.\n";
        }
    }

    return 0;
}
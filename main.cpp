
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

    while (i < (int)text.length())
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
        cout << "Invalid input. Please restart and enter a whole number.\n";
        return false;
    }

    return true;
}

bool readPrice(double &price)
{
    if (!(cin >> price))
    {
        cout << "Invalid price. Please restart and enter a number.\n";
        return false;
    }

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
    string name, location, cropName;

    while (true)
    {
        cout << "\n===== FARMER MENU =====\n";
        cout << "1. Add Farmer Details\n";
        cout << "2. View My Farmer Details\n";
        cout << "3. Update Farmer Details\n";
        cout << "4. Add Crop for Sale\n";
        cout << "5. View My Crops\n";
        cout << "6. Update My Crop Listing\n";
        cout << "7. Remove My Crop Listing\n";
        cout << "8. Logout\n";
        cout << "Enter choice: ";

        if (!readInteger(choice))
            return;

        if (choice == 1)
        {
            cout << "Enter farmer name (one word): ";
            cin >> name;

            cout << "Enter location (one word): ";
            cin >> location;

            if (hasSpace(name) || hasSpace(location))
            {
                cout << "Enter single-word name and location.\n";
            }
            else
            {
                farmer.setFarmerName(name);
                farmer.setLocation(location);

                if (!farmer.addFarmer())
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
            cout << "Enter new name (one word): ";
            cin >> name;

            cout << "Enter new location (one word): ";
            cin >> location;

            if (farmer.updateFarmer(username, name, location))
                cout << "Farmer details updated successfully.\n";
            else
                cout << "Farmer not found or update failed.\n";
        }
        else if (choice == 4)
        {
            cout << "Enter crop name (one word): ";
            cin >> cropName;

            cout << "Enter quantity in kg: ";
            if (!readInteger(quantity))
                return;

            if (quantity <= 0)
            {
                cout << "Quantity must be greater than zero.\n";
                continue;
            }

            cout << "Enter expected price per kg: ";

            if (!readPrice(price))
            {
                if (!cin)
                    return;

                continue;
            }

            CropInfo newCrop(username, cropName, quantity, price);
            newCrop.addCrop();
        }
        else if (choice == 5)
        {
            crop.viewMyCrops(username);
        }
        else if (choice == 6)
        {
            cout << "Enter crop name to update: ";
            cin >> cropName;

            cout << "Enter new quantity in kg: ";
            if (!readInteger(quantity))
                return;

            if (quantity <= 0)
            {
                cout << "Quantity must be greater than zero.\n";
                continue;
            }

            cout << "Enter new expected price per kg: ";

            if (!readPrice(price))
            {
                if (!cin)
                    return;

                continue;
            }

            crop.updateCrop(username, cropName, quantity, price);
        }
        else if (choice == 7)
        {
            cout << "Enter crop name to remove: ";
            cin >> cropName;

            crop.removeCrop(username, cropName);
        }
        else if (choice == 8)
        {
            cout << "Logged out successfully.\n";
            return;
        }
        else
        {
            cout << "Invalid choice. Select 1 to 8.\n";
        }
    }
}

// MANDI MENU
void mandiMenu(string username)
{
    Mandi mandi(username, "", "", "", vector<string>(),
                vector<double>(), 0);

    int choice;
    string name, location;

    while (true)
    {
        cout << "\n===== MANDI MENU =====\n";
        cout << "1. Add Mandi Details\n";
        cout << "2. View My Mandi Details\n";
        cout << "3. Update Mandi Details\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";

        if (!readInteger(choice))
            return;

        if (choice == 1)
        {
            // addMandi() prints its own result message.
            mandi.addMandi();
        }
        else if (choice == 2)
        {
            if (!mandi.viewMandi(username))
                cout << "Mandi details not found. Add them first.\n";
        }
        else if (choice == 3)
        {
            cout << "Enter new name (one word): ";
            cin >> name;

            cout << "Enter new location (one word): ";
            cin >> location;

            if (mandi.updateMandi(username, name, location))
                cout << "Mandi details updated successfully.\n";
            else
                cout << "Mandi not found or update failed.\n";
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
            return 0;

        if (choice == 1 || choice == 3)
        {
            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

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
                    cin >> password;
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
            cin >> username;

            cout << "Choose password: ";
            cin >> password;

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

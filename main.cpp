
#include "include/user.h"
#include "include/farmer.h"
#include "include/mandi.h"
#include <iostream>
#include <string>
using namespace std;

bool hasSpace(string s)
{
    int i = 0;

    while (i < s.length())
    {
        if (s[i] == ' ' || s[i] == '\t')
            return true;
        i++;
    }

    return false;
}

void farmerMenu(string username)
{
    Farmer farmer(username, "", "", "");
    int choice;
    string id, name, location;

    while (true)
    {
        cout << "\n===== FARMER MENU =====\n";
        cout << "1. Add Farmer Details\n";
        cout << "2. View Farmer Details\n";
        cout << "3. Search Farmer\n";
        cout << "4. Update Farmer Details\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (choice == 1)
        {
            cout << "Enter farmer name (one word): ";
            getline(cin, name);
            cout << "Enter location (one word): ";
            getline(cin, location);

            if (name == "" || location == "" ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Name and location must be non-empty single words.\n";
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
            farmer.viewFarmer(username);
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

            if (name == "" || location == "" ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Name and location must be non-empty single words.\n";
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
            cout << "Farmer logged out successfully.\n";
            return;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
}

void mandiMenu(string username)
{
    Mandi mandi(username, "", "", "");
    int choice;
    string id, name, location;

    while (true)
    {
        cout << "\n===== MANDI MENU =====\n";
        cout << "1. Add Mandi Details\n";
        cout << "2. View Mandi Details\n";
        cout << "3. Search Mandi\n";
        cout << "4. Update Mandi Details\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (choice == 1)
        {
            cout << "Enter mandi name (one word): ";
            getline(cin, name);
            cout << "Enter location (one word): ";
            getline(cin, location);

            if (name == "" || location == "" ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Name and location must be non-empty single words.\n";
            }
            else
            {
                mandi.setMandiName(name);
                mandi.setLocation(location);

                if (mandi.addMandi())
                    cout << "Mandi details added successfully.\n";
                else
                    cout << "Could not add details. They may already exist.\n";
            }
        }
        else if (choice == 2)
        {
            if (!mandi.viewMandi(username))
                cout << "Mandi details not found. Add them first.\n";
        }
        else if (choice == 3)
        {
            cout << "Enter mandi ID to search: ";
            getline(cin, id);

            if (!mandi.searchMandi(id))
                cout << "Mandi not found.\n";
        }
        else if (choice == 4)
        {
            cout << "Enter mandi ID to update: ";
            getline(cin, id);
            cout << "Enter new name (one word): ";
            getline(cin, name);
            cout << "Enter new location (one word): ";
            getline(cin, location);

            if (name == "" || location == "" ||
                hasSpace(name) || hasSpace(location))
            {
                cout << "Name and location must be non-empty single words.\n";
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
        else if (choice == 5)
        {
            cout << "Mandi logged out successfully.\n";
            return;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
}

int main()
{
    UserAuthentication auth;

    auth.loadFarmers();
    auth.loadMandis();

    int choice, attempts;
    string username, password;

    while (true)
    {
        cout << "\n===== WELCOME TO AGRICONNECT =====\n";
        cout << "1. Farmer Login\n";
        cout << "2. Farmer Registration\n";
        cout << "3. Mandi Login\n";
        cout << "4. Mandi Registration\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (choice == 1 || choice == 3)
        {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            if (username == "" || password == "")
            {
                cout << "Username and password cannot be empty.\n";
                continue;
            }

            if (hasSpace(username) || hasSpace(password))
            {
                cout << "Username and password cannot contain spaces.\n";
                continue;
            }

            if (choice == 1 && !auth.farmerUsernameExists(username))
            {
                cout << "Farmer username not found. Please register first.\n";
                continue;
            }

            if (choice == 3 && !auth.mandiUsernameExists(username))
            {
                cout << "Mandi username not found. Please register first.\n";
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
                    cout << "Incorrect password. " << attempts
                         << " attempt(s) left.\n";
                    cout << "Enter password again: ";
                    getline(cin, password);

                    if (password == "" || hasSpace(password))
                    {
                        cout << "Invalid password format.\n";
                        break;
                    }
                }
                else
                {
                    cout << "Too many incorrect attempts. Try again later.\n";
                }
            }

            if (loggedIn)
            {
                if (choice == 1)
                {
                    cout << "Farmer login successful!\n";
                    farmerMenu(username);
                }
                else
                {
                    cout << "Mandi login successful!\n";
                    mandiMenu(username);
                }
            }
        }
        else if (choice == 2 || choice == 4)
        {
            cout << "Choose a username: ";
            getline(cin, username);
            cout << "Choose a password: ";
            getline(cin, password);

            if (username == "" || password == "")
            {
                cout << "Username and password cannot be empty.\n";
            }
            else if (hasSpace(username) || hasSpace(password))
            {
                cout << "Username and password cannot contain spaces.\n";
            }
            else if (choice == 2)
            {
                if (auth.registerFarmer(username, password))
                {
                    cout << "Farmer registration successful!\n";
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
                    cout << "Mandi registration successful!\n";
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

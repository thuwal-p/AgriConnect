
#include "include/user.h"

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

int main()
{
    UserAuthentication auth;

    auth.loadFarmers();
    auth.loadMandis();

    int choice;
    int attempts;
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
            cout << "Please enter a valid number.\n";
            break;
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
                cout << "Error: Username and password cannot be empty.\n";
            }
            else if (hasSpace(username) || hasSpace(password))
            {
                cout << "Friendly reminder: Username and password cannot contain spaces.\n";
            }
            else if (choice == 1 && !auth.farmerUsernameExists(username))
            {
                cout << "Farmer username not found. Please register first.\n";
            }
            else if (choice == 3 && !auth.mandiUsernameExists(username))
            {
                cout << "Mandi username not found. Please register first.\n";
            }
            else
            {
                attempts = 3;

                while (attempts > 0)
                {
                    if (choice == 1)
                    {
                        if (auth.farmerLogin(username, password))
                        {
                            cout << "Welcome back, Farmer!\n";
                            break;
                        }
                    }
                    else
                    {
                        if (auth.mandiLogin(username, password))
                        {
                            cout << "Welcome back, Mandi!\n";
                            break;
                        }
                    }

                    attempts--;

                    if (attempts > 0)
                    {
                        cout << "Incorrect password. "
                             << attempts << " attempt(s) left.\n";

                        cout << "Enter password again: ";
                        getline(cin, password);

                        if (password == "")
                        {
                            cout << "Error: Password cannot be empty.\n";
                            break;
                        }
                        else if (hasSpace(password))
                        {
                            cout << "Friendly reminder: Password cannot contain spaces.\n";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Too many incorrect attempts. Please try again later.\n";
                    }
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
                cout << "Error: Username and password cannot be empty.\n";
            }
            else if (hasSpace(username) || hasSpace(password))
            {
                cout << "Friendly reminder: Username and password cannot contain spaces.\n";
            }
            else if (choice == 2)
            {
                if (auth.registerFarmer(username, password))
                    cout << "Farmer registration successful! Welcome to AgriConnect.\n";
                else
                    cout << "This username already exists or the account could not be saved.\n";
            }
            else
            {
                if (auth.registerMandi(username, password))
                    cout << "Mandi registration successful! Welcome to AgriConnect.\n";
                else
                    cout << "This username already exists or the account could not be saved.\n";
            }
        }
        else if (choice == 5)
        {
            cout << "Thank you for using AgriConnect. Have a great day!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please select 1 to 5.\n";
        }
    }

    return 0;
}
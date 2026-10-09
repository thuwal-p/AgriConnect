
#include "include/user.h"

int main()
{
    UserAuthentication auth;

    auth.loadFarmers();
    auth.loadMandis();

    int choice;
    string username, password;

    while (true)
    {
        cout << "\n===== AgriConnect =====\n";
        cout << "1. Farmer Login\n";
        cout << "2. Farmer Registration\n";
        cout << "3. Mandi Login\n";
        cout << "4. Mandi Registration\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            if (auth.farmerLogin(username, password))
            {
                cout << "Farmer login successful!\n";
            }
            else
            {
                cout << "Invalid username or password.\n";
            }
        }
        else if (choice == 2)
        {
            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            if (auth.registerFarmer(username, password))
            {
                cout << "Farmer registered successfully!\n";
            }
            else
            {
                cout << "Registration failed.USERNAME ALREADY EXITS\n";
            }
        }
        else if (choice == 3)
        {
            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            if (auth.mandiLogin(username, password))
            {
                cout << "Mandi login successful!\n";
            }
            else
            {
                cout << "Invalid username or password.\n";
            }
        }
        else if (choice == 4)
        {
            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            if (auth.registerMandi(username, password))
            {
                cout << "Mandi registered successfully!\n";
            }
            else
            {
                cout << "Registration failed.USERNAME ALREADY EXITS\n";
            }
        }
        else if (choice == 5)
        {
            cout << "Exiting AgriConnect.\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}



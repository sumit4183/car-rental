#include <iostream>
#include <string>

#include "../include/user.h"

// Database functions
extern bool openDatabase(const char* filename);
extern void closeDatabase();
extern bool initializeDatabase();

using namespace std;

// Function to display the menu options to the user
void showMenu()
{
    cout << "1. Register new user" << endl;
    cout << "2. Login existing user" << endl;
    cout << "3. Update user" << endl;
    cout << "4. Delete user" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

int main()
{

    // Open the database connection
    if (!openDatabase("car_rental.db"))
    {
        return 1;
    }

    // Initialize the database (create tables if they don't exist)
    if (!initializeDatabase())
    {
        closeDatabase();        // Close the database if initialization fails
        return 1;
    }

    int choice;     // Variable to store the user's menu choice
    while (true)
    {
        showMenu();
        cin >> choice;  // Get the user's choice
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        if (choice == 1)
        {
            // Register new user
            string username, password, name, email;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter email: ";
            getline(cin, email);

            if (registerUser(username, password, name, email))
            {
                cout << "User registered successfully!" << endl << endl;
            } 
            else
            {
                cout << "User registration failed." << endl << endl;
            }
        }
        else if (choice == 2)
        {
            // Login existing user
            string username, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            if (loginUser(username, password))
            {
                cout << "User logged in successfully!" << endl << endl;
            }
            else
            {
                cout << "User login failed." << endl << endl;
            }
        }
        else if (choice == 3)
        {
            string username, name, password;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter password: ";
            getline(cin, password);

            if (updateUserProfile(username, name, password))
            {
                cout << "User updated successfully!" << endl << endl;
            }
            else
            {
                cout << "User updation failed." << endl << endl;
            }
        }
        else if (choice == 4)
        {
            // Delete user
            string username;
            cout << "Enter username to delete: ";
            getline(cin, username);

            if (deleteUser(username))
            {
                cout << "User deleted successfully!" << endl << endl;
            }
            else
            {
                cout << "User deletion failed." << endl << endl;
            }
        }
        else if (choice == 5)
        {
            break; // Exit the loop and the end program
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    }

    closeDatabase();
    return 0;
}
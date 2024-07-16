#include <iostream>
#include <string>

#include "../include/inputs.h"
#include "../include/user.h"
#include "../include/car.h"

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
    cout << "5. Add car" << endl;
    cout << "6. Edit car" << endl;
    cout << "7. List cars" << endl;
    cout << "8. Get Car Details" << endl;
    cout << "9. Book a car" << endl;
    cout << "10. Cancel booking" << endl;
    cout << "11. List bookings" << endl;
    cout << "999. Exit" << endl;
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
            // Add car
            Car car;
            cout << "Enter type: ";
            getline(cin, car.type);
            cout << "Enter make: ";
            getline(cin, car.make);
            cout << "Enter model: ";
            getline(cin, car.model);
            cout << "Enter year: ";
            cin >> car.year;
            cout << "Enter rental price: ";
            cin >> car.rental_price;
            car.available = true;

            if (addCar(car))
            {
                cout << "Car added successfully!" << endl << endl;
            }
            else
            {
                cout << "Failed to add car." << endl << endl;
            }
        }
        else if (choice == 6)
        {
            // Edit car
            Car car;
            cout << "Enter car ID to edit: ";
            cin >> car.id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
            cout << "Enter new type: ";
            getline(cin, car.type);
            cout << "Enter new make: ";
            getline(cin, car.make);
            cout << "Enter new model: ";
            getline(cin, car.model);
            cout << "Enter new year: ";
            cin >> car.year;
            cout << "Enter new rental price: ";
            cin >> car.rental_price;
            cout << "Is the car available (1 for Yes, 0 for No): ";
            cin >> car.available;

            if (editCar(car))
            {
                cout << "Car edited successfully!" << endl << endl;
            }
            else
            {
                cout << "Failed to edit car." << endl << endl;
            }
        }
        else if (choice == 7)
        {
            // List cars
            listCars();
        }
        else if (choice == 8)
        {
            // string 
        }
        else if (choice == 9 || choice == 10 || choice == 11)
        {
            bookingInput(choice);
        }
        else if (choice == 999)
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
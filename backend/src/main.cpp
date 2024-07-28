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
    cout << endl;
    cout << "1. Register new user" << endl;
    cout << "2. Login existing user" << endl;
    cout << "3. Update user" << endl;
    cout << "4. Delete user" << endl;
    cout << "11. Add car" << endl;
    cout << "12. Edit car" << endl;
    cout << "13. List cars" << endl;
    cout << "14. Filter Cars by Type" << endl;
    cout << "15. Filter Cars by Rental Price" << endl;
    cout << "21. Book a car" << endl;
    cout << "22. Cancel booking" << endl;
    cout << "23. List bookings" << endl;
    cout << "24. List Bookings by User" << endl;
    cout << "31. Process payment" << endl;
    cout << "32. List payments" << endl;
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
        cout << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
        // Taking User inputs
        if (choice >= 1 && choice <= 4)
        {
            userInput(choice);
        }
        // Taking Car Inputs
        else if (choice >= 11 && choice <= 15)
        {
            carInput(choice);
        }
        // Taking Booking Inputs
        else if (choice >= 21 && choice <= 24)
        {
            bookingInput(choice);
        }
        // Taking Payment Inputs
        else if (choice >= 31 && choice <= 32)
        {
            paymentInput(choice);
        }
        // Exit
        else if (choice == 999)
        {
            break; // Exit the loop and the end program
        }
        // Invalid choice
        else
        {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    }

    closeDatabase();
    return 0;
}
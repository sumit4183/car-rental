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
    cout << "5. Add car" << endl;
    cout << "6. Edit car" << endl;
    cout << "7. List cars" << endl;
    cout << "8. Get Car Details" << endl;
    cout << "9. Book a car" << endl;
    cout << "10. Cancel booking" << endl;
    cout << "11. List bookings" << endl;
    cout << "12. Process payment" << endl;
    cout << "13. List payments" << endl;
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
        // Taking user inputs
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
        {
            userInput(choice);
        }
        // Taking Car Inputs
        else if (choice == 5 || choice == 6 || choice == 7 || choice == 8)
        {
            carInput(choice);
        }
        // Taking Booking Inputs
        else if (choice == 9 || choice == 10 || choice == 11)
        {
            bookingInput(choice);
        }
        // Taking Payment Inputs
        else if (choice == 12 || choice == 13)
        {
            paymentInput(choice);
        }
        // Exit
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
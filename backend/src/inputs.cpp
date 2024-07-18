#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "../include/helper.h"
#include "../include/user.h"
#include "../include/car.h"
#include "../include/booking.h"
#include "../include/payment.h"

using namespace std;

void userInput(int choice)
{
    // Register new user
    if (choice == 1)
    {
        string username, password, name, email;
        cout << "Enter username: ";
        getline(cin, username);
        // CHANGE PASSWORD REQUIREMENTS
        // HASH PASSWORD
        // CONFIRM PASSWORD
        cout << "Enter password: ";
        getline(cin, password);
        cout << "Enter name: ";
        getline(cin, name);
        // CHANGE EMAIL TO ALL LOWER CASE
        cout << "Enter email: ";
        getline(cin, email);

        if (registerUser(username, password, name, email))
        {
            cout << "User registered successfully!" << endl;
        } 
        else
        {
            cout << "User registration failed." << endl;
        }
    }
    // Login existing user
    else if (choice == 2)
    {
        string username, password;
        cout << "Enter username: ";
        getline(cin, username);
        // CHANGE TO HASH
        cout << "Enter password: ";
        getline(cin, password);

        if (loginUser(username, password))
        {
            cout << "User logged in successfully!" << endl;
        }
        else
        {
            cout << "User login failed." << endl;
        }
    }
    // Update User Profile
    else if (choice == 3)
    {
        string username, name, password;
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter name: ";
        getline(cin, name);
        // CHANGE PASSWORD REQUIREMENTS
        // HASH PASSWORD
        cout << "Enter password: ";
        getline(cin, password);

        if (updateUserProfile(username, name, password))
        {
            cout << "User updated successfully!" << endl;
        }
        else
        {
            cout << "User updation failed." << endl;
        }
    }
    // Delete user
    else if (choice == 4)
    {
        string username;
        // ASK FOR CONFIRMATION
        cout << "Enter username to delete: ";
        getline(cin, username);

        if (deleteUser(username))
        {
            cout << "User deleted successfully!" << endl;
        }
        else
        {
            cout << "User deletion failed." << endl;
        }
    }
}

void carInput(int choice)
{
    // Add car
    if (choice == 5)
    {
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
    // Edit car
    else if (choice == 6)
    {
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
    // List cars
    else if (choice == 7)
    {
        listCars();
    }
    else if (choice == 8)
    {
        // string 
    }
}

void bookingInput(int choice)
{
    // Book a Car
    if (choice == 9)
    {
        // Book a car
        Booking booking;
        // CHECK IF USER AND CAR EXIST
        cout << "Enter user ID: ";
        cin >> booking.user_id;
        cout << "Enter car ID: ";
        cin >> booking.car_id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        // Input and validate start date and time
        do {
            cout << "Enter start date (YYYY-MM-DD): ";
            getline(cin, booking.start_date);
            cout << "Enter start time (HH:MM): ";
            getline(cin, booking.start_time);
            if (!isValidDateTime(booking.start_date, booking.start_time)) {
                cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl;
            }
        } while (!isValidDateTime(booking.start_date, booking.start_time));
        
        // Input and validate end date and time
        do {
            cout << "Enter end date (YYYY-MM-DD): ";
            getline(cin, booking.end_date);
            cout << "Enter end time (HH:MM): ";
            getline(cin, booking.end_time);
            if (!isValidDateTime(booking.end_date, booking.end_time)) {
                cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl;
            }
        } while (!isValidDateTime(booking.end_date, booking.end_time));
        
        // BOOKING DATE MUST BE THE SAME OR BEFORE START DATE
        // Input and validate booking date and time
        do {
            cout << "Enter booking date (YYYY-MM-DD): ";
            getline(cin, booking.booking_date);
            cout << "Enter booking time (HH:MM): ";
            getline(cin, booking.booking_time);
            if (!isValidDateTime(booking.booking_date, booking.booking_time)) {
                cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl;
            }
        } while (!isValidDateTime(booking.booking_date, booking.booking_time));

        // Calculate the number of rental days
        tm start_tm = {};
        tm end_tm = {};
        istringstream ss_start(booking.start_date + " " + booking.start_time);
        istringstream ss_end(booking.end_date + " " + booking.end_time);
        ss_start >> get_time(&start_tm, "%Y-%m-%d %H:%M");
        ss_end >> get_time(&end_tm, "%Y-%m-%d %H:%M");
        time_t start_time = mktime(&start_tm);
        time_t end_time = mktime(&end_tm);

        // Ensure the end time is after the start time
        if (difftime(end_time, start_time) <= 0) {
            cout << "End date/time must be after start date/time." << endl;
            return ;
        }

        // Ensure the rental period is at least one hour
        double rental_hours = difftime(end_time, start_time) / (60 * 60);
        if (rental_hours < 1) {
            cout << "The rental period must be at least one hour." << endl;
            return ;
        }

        // Calculate rental days, rounding up any partial day
        double rental_days = ceil(difftime(end_time, start_time) / (60 * 60 * 24));

        double rental_price_per_day;
        if (getCarRentalPrice(booking.car_id, rental_price_per_day)) {
            booking.total_price = rental_price_per_day * rental_days;
            booking.amt_left = booking.total_price;
            if (addBooking(booking)) {
                cout << "Total price: $" << booking.total_price << endl;
                cout << "Booking added successfully!" << endl;
            } else {
                cout << "Failed to add booking." << endl;
            }
        } else {
            cout << "Failed to retrieve car rental price. Please try again." << endl;
        }
    }
    // Cancel Booking
    else if (choice == 10)
    {
        // Cancel booking
        int bookingId;
        cout << "Enter booking ID to cancel: ";
        cin >> bookingId;

        if (cancelBooking(bookingId))
        {
            cout << "Booking cancelled successfully!" << endl;
        }
        else
        {
            cout << "Failed to cancel booking." << endl;
        }
    }
    // List all Bookings
    else if (choice == 11)
    {
        // List bookings
        listBookings();
    }
}

// ADD BOOKING AND PAYMENT HISTORY FOR SPECFIC USERS

void paymentInput(int choice)
{
    // Process Payments
    if (choice == 12)
    {
        // Process payment
        Payment payment;
        cout << "Enter user ID: ";
        cin >> payment.user_id;
        cout << "Enter booking ID: ";
        cin >> payment.booking_id;
        cout << "Enter amount: ";
        cin >> payment.amount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        // Validate date and time
        do {
            cout << "Enter payment date (YYYY-MM-DD): ";
            getline(cin, payment.payment_date);
            cout << "Enter payment time (HH:MM): ";
            getline(cin, payment.payment_time);
            if (!isValidDateTime(payment.payment_date, payment.payment_time)) {
                cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl;
            }
        } while (!isValidDateTime(payment.payment_date, payment.payment_time));


        if (processPayment(payment))
        {
            cout << "Payment processed successfully!" << endl;
            return;
        }
        else
        {
            cout << "Failed to process payment." << endl;
        }
    }
    // List all payments
    else if (choice == 13)
    {
        // ADJUST ALIGNMENT
        // List payments
        listPayments();
    }
}
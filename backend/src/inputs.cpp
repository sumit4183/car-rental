#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "../include/inputs.h"
#include "../include/helper.h"
#include "../include/user.h"
#include "../include/car.h"
#include "../include/booking.h"
#include "../include/payment.h"

using namespace std;

// DELETE ALL USER DATA WHEN DELETING USER
void userInput(int choice)
{
    switch (choice) {
        case 1: registerUserInput(); break;
        case 2: loginUserInput(); break;
        case 3: updateUserInput(); break;
        case 4: deleteUserInput(); break;
    }
}

// UPDATE CAR AVAILABILITY WHEN BOOKING
void carInput(int choice) 
{
    switch (choice) {
        case 11: addCarInput(); break;
        case 12: editCarInput(); break;
        case 13: listCars(); break;
        case 14: filterCarsByTypeInput(); break;
        case 15: filterCarsByRentalPriceInput(); break;
    }
}

void bookingInput(int choice)
{
    switch (choice) {
        case 21: bookCarInput(); break;
        case 22: cancelBookInput(); break;
        case 23: listBookings(); break;
        case 24: listUserBookInput(); break;
    }
}

// NOT RETURNING HALF PAYMENT IF CANCELLING CAR ON PICKUP DATE

void paymentInput(int choice)
{
    switch (choice) {
        case 31: processPayInput(); break;
        case 32: listPayments(); break;
        case 33: listUserPayInput(); break;
    }
}

// User Inputs
void registerUserInput()
{
    string username, password, confirmPassword, name, email;
    // Username input
    cout << "Enter username: ";
    getline(cin, username);
    // Password input
    cout << "Enter password: ";
    getline(cin, password);
    // Password Requirements
    if (!validatePassword(password))
    {
        cout << "Passwords Requirements:" << endl;
        cout << "Minimum length (e.g., 8 characters)" << endl;
        cout << "At least one uppercase letter" << endl;
        cout << "At least one lowercase letter" << endl;
        cout << "At least one digit" << endl;
        cout << "At least one special character" << endl;
        return;
    }
    // Confirm Password input
    cout << "Confirm password: ";
    getline(cin, confirmPassword);
    if (password != confirmPassword)
    {
        cout << "Passwords do not match." << endl;
        cout << "User registration failed." << endl;
        return;
    }
    // User's name input
    cout << "Enter name: ";
    getline(cin, name);
    // User's email input
    cout << "Enter email: ";
    getline(cin, email);
    // Email to lower case
    transform(email.begin(), email.end(), email.begin(), ::tolower);

    if (registerUser(username, password, name, email))
    {
        cout << "User registered successfully!" << endl;
    } 
    else
    {
        cout << "User registration failed." << endl;
    }
}

void loginUserInput()
{
    string username, password;
    // User's name input
    cout << "Enter username: ";
    getline(cin, username);
    // Password input
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

void updateUserInput()
{
    string username, name, password, confirmPassword;
    // Username input
    cout << "Enter username: ";
    getline(cin, username);
    // User's name input
    cout << "Enter name: ";
    getline(cin, name);
    // Password input
    cout << "Enter password: ";
    getline(cin, password);
    // Password Requirements
    if (!validatePassword(password))
    {
        cout << "Passwords Requirements:" << endl;
        cout << "Minimum length (e.g., 8 characters)" << endl;
        cout << "At least one uppercase letter" << endl;
        cout << "At least one lowercase letter" << endl;
        cout << "At least one digit" << endl;
        cout << "At least one special character" << endl;
        return;
    }
    // Confirm Password
    cout << "Confirm password: ";
    getline(cin, confirmPassword);
    if (password != confirmPassword)
    {
        cout << "Passwords do not match." << endl;
        cout << "User updation failed." << endl;
        return;
    }

    if (updateUserProfile(username, name, password))
    {
        cout << "User updated successfully!" << endl;
    }
    else
    {
        cout << "User updation failed." << endl;
    }
}

void deleteUserInput()
{
    string username, confirmUsername;
    // Username input
    cout << "Enter username to delete: ";
    getline(cin, username);
    // Confirm username
    cout << "Confirm password: ";
    getline(cin, confirmUsername);
    if (username != confirmUsername)
    {
        cout << "Usernames do not match." << endl;
        cout << "User deletion failed." << endl;
        return;
    }

    if (deleteUser(username))
    {
        cout << "User deleted successfully!" << endl;
    }
    else
    {
        cout << "User deletion failed." << endl;
    }
}

// Car Inputs
void addCarInput()
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

void editCarInput()
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

void filterCarsByTypeInput()
{
    string type;
    cout << "Enter type: ";
    cin >> type;
    filterCarsByType(type);
}

void filterCarsByRentalPriceInput()
{
    double minPrice, maxPrice;
    cout << "Enter minimum rental price: ";
    cin >> minPrice;
    cout << "Enter maximum rental price: ";
    cin >> maxPrice;
    filterCarsByRentalPrice(minPrice, maxPrice);
}

// Booking Inputs
void bookCarInput()
{
    // Book a car
    Booking booking;
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
        return;
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

void cancelBookInput()
{
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

void listUserBookInput()
{
    int userId;
    cout << "Enter user ID to view booking history: ";
    cin >> userId;

    listUserBookings(userId);
}

// Payment Inputs
void processPayInput()
{
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

void listUserPayInput()
{
    int userId;
    cout << "Enter user ID to view payment history: ";
    cin >> userId;

    listUserPayments(userId);
}

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "../include/booking.h"
#include "../include/helper.h"

using namespace std;

void bookingInput(int choice)
{
    if (choice == 9)
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
                cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl << endl;
            }
        } while (!isValidDateTime(booking.start_date, booking.start_time));
        
        // Input and validate end date and time
        do {
            cout << "Enter end date (YYYY-MM-DD): ";
            getline(cin, booking.end_date);
            cout << "Enter end time (HH:MM): ";
            getline(cin, booking.end_time);
            if (!isValidDateTime(booking.end_date, booking.end_time)) {
                cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl << endl;
            }
        } while (!isValidDateTime(booking.end_date, booking.end_time));

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
            cout << "End date/time must be after start date/time." << endl << endl;
            return ;
        }

        // Ensure the rental period is at least one hour
        double rental_hours = difftime(end_time, start_time) / (60 * 60);
        if (rental_hours < 1) {
            cout << "The rental period must be at least one hour." << endl << endl;
            return ;
        }

        // Calculate rental days, rounding up any partial day
        double rental_days = ceil(difftime(end_time, start_time) / (60 * 60 * 24));

        double rental_price_per_day;
        if (getCarRentalPrice(booking.car_id, rental_price_per_day)) {
            booking.total_price = rental_price_per_day * rental_days;
            if (addBooking(booking)) {
                cout << "Total price: $" << booking.total_price << endl;
                cout << "Booking added successfully!" << endl << endl;
            } else {
                cout << "Failed to add booking." << endl << endl;
            }
        } else {
            cout << "Failed to retrieve car rental price. Please try again." << endl << endl;
        }
    }
    else if (choice == 10)
    {
        // Cancel booking
        int bookingId;
        cout << "Enter booking ID to cancel: ";
        cin >> bookingId;

        if (cancelBooking(bookingId))
        {
            cout << "Booking cancelled successfully!" << endl << endl;
        }
        else
        {
            cout << "Failed to cancel booking." << endl << endl;
        }
    }
    else if (choice == 11)
    {
        // List bookings
        listBookings();
    }
}
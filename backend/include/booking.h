#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <sqlite3.h>

using namespace std;

struct Booking {
    int id;
    int user_id;
    int car_id;
    std::string start_time;
    std::string end_time;
    std::string start_date;
    std::string end_date;
    std::string booking_date;
    std::string booking_time;
    double total_price;
    double amt_left;
};

bool addBooking(const Booking& booking);
bool getCarRentalPrice(int carId, double& rental_price);
bool cancelBooking(int bookingId, string currentDate);
void listBookings();
bool listUserBookings(int userId);
void printBookListHeader();
void printBookDetails(sqlite3_stmt* stmt);
bool deleteAllBookings(int userId);

#endif // BOOKING_H
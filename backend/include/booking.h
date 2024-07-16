#ifndef BOOKING_H
#define BOOKING_H

#include <string>

using namespace std;

struct Booking {
    int id;
    int user_id;
    int car_id;
    string start_time;
    string end_time;
    string start_date;
    string end_date;
    double total_price;
};

bool addBooking(const Booking& booking);
bool getCarRentalPrice(int carId, double& rental_price);
bool cancelBooking(int bookingId);
void listBookings();

#endif // BOOKING_H
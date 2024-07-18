#ifndef HELPER_H
#define HELPER_H

#include <string>

#include "user.h"
#include "booking.h"
#include "car.h"

using namespace std;

bool checkUser(const std::string& username);
bool getUserDetails(int user_id, User& details);
bool getBookingDetails(int booking_id, Booking& details);
bool getCarDetails(int car_id, Car& details);
bool isValidDateTime(const std::string& date, const std::string& time);
bool updateRemainingAmt(int booking_id, double remaining_amount);

#endif // HELPER_H
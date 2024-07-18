#ifndef HELPER_H
#define HELPER_H

#include <string>

#include "booking.h"
#include "user.h"

using namespace std;

bool checkUser(const std::string& username);
bool getUserDetails(int user_id, User& details);
bool isValidDateTime(const std::string& date, const std::string& time);
bool getBookingDetails(int booking_id, Booking& details);
bool updateRemainingAmt(int booking_id, double remaining_amount);

#endif // HELPER_H
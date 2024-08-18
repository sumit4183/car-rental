#ifndef HELPER_H
#define HELPER_H

#include <string>

#include "user.h"
#include "booking.h"
#include "car.h"

using namespace std;

string hashPassword(const string& password);
bool getUserDetails(int user_id, const std::string& username, User& details);
bool getBookingDetails(int booking_id, Booking& details);
bool getCarDetails(int car_id, Car& details);
bool getInputAndValidateDateTime(string& date, string& time, const string& promptDate, const string& promptTime);
bool isValidDateTime(const std::string& date, const std::string& time);
bool isBookingDateValid(const string& booking_date, const string& start_date);
bool isValidEmail(const string& email);
bool validatePassword(const string& password);
bool updateRemainingAmt(int booking_id, double remaining_amount);
bool isCarAvailable(int car_id, const string& start_date, const string& end_date);


#endif // HELPER_H
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <sqlite3.h>
#include <openssl/sha.h>

using namespace std;

#include "../include/helper.h"
#include "../include/user.h"
#include "../include/booking.h"
#include "../include/car.h"

extern sqlite3* db;

// Function to hash password
string hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
 
// Function to get all detail of the user if exists
bool getUserDetails(int user_id, const string& username, User& details)
{
    string sql = "";
    if (user_id == 0)
    {
        sql = "SELECT * FROM users WHERE username = ?;";
    }
    else
    {
        sql = "SELECT * FROM users WHERE id = ?;";
    }

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    if (user_id == 0)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    }
    else
    {
        sqlite3_bind_int(stmt, 1, user_id);
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        details.id = sqlite3_column_int(stmt, 0);
        details.username = sqlite3_column_int(stmt, 1);
        details.password = sqlite3_column_int(stmt, 2);
        details.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        details.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        sqlite3_finalize(stmt);
        return true;
    } else {
        sqlite3_finalize(stmt);
        cout << "User does not exist" << endl;
        return false;
    }
}

// Function to get all detail of the booking if exists
bool getBookingDetails(int booking_id, Booking& details)
{
    string sql = "SELECT * FROM bookings WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, booking_id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        details.id = sqlite3_column_int(stmt, 0);
        details.user_id = sqlite3_column_int(stmt, 1);
        details.car_id = sqlite3_column_int(stmt, 2);
        details.start_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        details.end_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        details.start_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        details.end_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        details.booking_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        details.booking_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        details.total_price = sqlite3_column_double(stmt, 9);
        details.amt_left = sqlite3_column_double(stmt, 10);
        sqlite3_finalize(stmt);
        return true;
    } else {
        sqlite3_finalize(stmt);
        cout << "Booking does not exist" << endl;
        return false;
    }
}

// Function to get all detail of the car if exists
bool getCarDetails(int car_id, Car& details)
{
    // SQL query to select car details
    string sql = "SELECT * FROM cars WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind the car_id to the SQL statement
    sqlite3_bind_int(stmt, 1, car_id);

    // Execute the query and retrieve the car details
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        details.id = sqlite3_column_int(stmt, 0);
        details.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        details.make = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        details.model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        details.year = sqlite3_column_int(stmt, 4);
        details.rental_price = sqlite3_column_double(stmt, 5);
        details.available = sqlite3_column_int(stmt, 6);

        sqlite3_finalize(stmt);
        return true;
    }
    else
    {
        cout << "Car not found." << endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

// Function to handle the input and validation of date and time:
bool getInputAndValidateDateTime(string& date, string& time, const string& promptDate, const string& promptTime)
{
    do {
        cout << promptDate;
        getline(cin, date);
        cout << promptTime;
        getline(cin, time);
        if (!isValidDateTime(date, time)) {
            cout << "Invalid date/time format. Please enter the date in YYYY-MM-DD and time in HH:MM format." << endl;
        }
    } while (!isValidDateTime(date, time));
    
    return true;
}

// Function to validate date and time format
bool isValidDateTime(const string& date, const string& time) {
    // Regex pattern for YYYY-MM-DD
    regex date_pattern(R"(\d{4}-\d{2}-\d{2})");
    regex time_pattern(R"(\d{2}:\d{2})");
    if (regex_match(date, date_pattern) && regex_match(time, time_pattern)) {
        // Further check to validate the actual date values
        tm tm = {};
        istringstream ss(date + " " + time);
        ss >> get_time(&tm, "%Y-%m-%d %H:%M");
        return !ss.fail();
    }
    return false;
}

bool isBookingDateValid(const string& booking_date, const string& start_date)
{
    // Compare the two dates directly since they are in the format YYYY-MM-DD
    return booking_date <= start_date;
}

// Function to validate email format
bool isValidEmail(const string& email)
{
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.(\w+))+)");
    return regex_match(email, pattern);
}

// Function to check password requirements
bool validatePassword(const string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Function to update amount left to pay
bool updateRemainingAmt(int booking_id, double remaining_amount) {
    string sql = "UPDATE bookings SET amt_left = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare update statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_double(stmt, 1, remaining_amount);
    sqlite3_bind_int(stmt, 2, booking_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Update execution failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}


bool isCarAvailable(int car_id, const string& start_date, const string& end_date)
{
    // Check for any overlapping bookings
    string sql = "SELECT COUNT(*) FROM bookings WHERE car_id = ? AND (start_date <= ? AND end_date >= ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, car_id);
    sqlite3_bind_text(stmt, 2, end_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, start_date.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count == 0;
    }
    else
    {
        sqlite3_finalize(stmt);
        return false;
    }
}

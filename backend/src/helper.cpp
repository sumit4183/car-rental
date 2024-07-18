#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <sqlite3.h>

using namespace std;

#include "../include/user.h"
#include "../include/booking.h"
#include "../include/car.h"

extern sqlite3* db;


bool checkUser(const string& username) {
    // Check if the username exists
    string checkSql = "SELECT COUNT(*) FROM users WHERE username = ?;";
    sqlite3_stmt* checkStmt;
    int rc2 = sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr);

    if (rc2 != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind the username to the SQL statement
    sqlite3_bind_text(checkStmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc2 = sqlite3_step(checkStmt);
    if (rc2 != SQLITE_ROW)
    {
        cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(checkStmt);
        return false;
    }
    int count = sqlite3_column_int(checkStmt, 0);
    sqlite3_finalize(checkStmt);
    if (count == 0)
    {
        cout << "Username " << username << " does not exist." << endl;
        return false;
    }

    return true;
}

bool getUserDetails(int user_id, User& details)
{
    string sql = "SELECT * FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, user_id);

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

bool getCarDetails(int car_id, Car& details)
{

}

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
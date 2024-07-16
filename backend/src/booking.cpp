#include <sqlite3.h>
#include <iostream>

#include "../include/booking.h"

using namespace std;

extern sqlite3* db;

// Function to add a new booking
bool addBooking(const Booking& booking)
{
    // Find the smallest available ID for the new booking
    string findIdSql = R"(
        SELECT id + 1
        FROM bookings b1
        WHERE NOT EXISTS (SELECT 1 FROM bookings b2 WHERE b2.id = b1.id + 1)
        ORDER BY b1.id
        LIMIT 1;
    )";
    sqlite3_stmt* findIdStmt;
    int rc = sqlite3_prepare_v2(db, findIdSql.c_str(), -1, &findIdStmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    int nextId = 0;
    rc = sqlite3_step(findIdStmt);      // Execute the SQL statement
    if (rc == SQLITE_ROW)           // If a row is returned, get the next available ID
    {       
        nextId = sqlite3_column_int(findIdStmt, 0);
    }
    else
    {
        // If no gaps are found, findIdSql returns no rows, and we should start from the highest ID + 1
        string maxIdSql = "SELECT COALESCE(MAX(id), 0) + 1 FROM bookings;";
        sqlite3_stmt* maxIdStmt;
        rc = sqlite3_prepare_v2(db, maxIdSql.c_str(), -1, &maxIdStmt, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        rc = sqlite3_step(maxIdStmt);
        if (rc == SQLITE_ROW)       // If a row is returned, get the next available ID
        {       
            nextId = sqlite3_column_int(maxIdStmt, 0);
        }
        sqlite3_finalize(maxIdStmt);
    }
    sqlite3_finalize(findIdStmt);

    // Insert the new booking with the calculated ID
    string sql = "INSERT INTO bookings (id, user_id, car_id, start_date, end_date, start_time, end_time, total_price) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind values to the SQL statement
    sqlite3_bind_int(stmt, 1, nextId);
    sqlite3_bind_int(stmt, 2, booking.user_id);
    sqlite3_bind_int(stmt, 3, booking.car_id);
    sqlite3_bind_text(stmt, 4, booking.start_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, booking.end_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, booking.start_time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, booking.end_time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, booking.total_price);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// Function to get the rental price of a car by its ID
bool getCarRentalPrice(int carId, double& rental_price)
{
    // SQL query to retrieve the rental price of a car
    string sql = "SELECT rental_price FROM cars WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, carId);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        rental_price = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return true;
    }
    else
    {
        cerr << "Car not found." << endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

// Function to cancel a booking
bool cancelBooking(int bookingId)
{
    // SQL query to delete a booking
    string sql = "DELETE FROM bookings WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, bookingId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// Function to list all bookings
void listBookings()
{
    // SQL query to retrieve all booking records
    string sql = "SELECT * FROM bookings;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Print header for the booking listings
    cout << "Booking Listings:" << endl;
    cout << "ID\tUser ID\tCar ID\tStart Date\tStart Time\tEnd Date\tEnd Time\tTotal Price" << endl;

    // Loop through the result set and print each booking's details
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int user_id = sqlite3_column_int(stmt, 1);
        int car_id = sqlite3_column_int(stmt, 2);
        string start_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string end_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        string start_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        string end_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        double total_price = sqlite3_column_double(stmt, 7);

        cout << id << "\t" << user_id << "\t" << car_id << "\t" << start_date << "\t" << start_time << "\t" << end_date << "\t" << end_time << "\t" << total_price << endl;
    }

    sqlite3_finalize(stmt);
}
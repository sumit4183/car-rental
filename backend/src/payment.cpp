#include <sqlite3.h>
#include <iostream>
#include <iomanip>

#include "../include/payment.h"
#include "../include/helper.h"

using namespace std;

extern sqlite3* db;

// Function to process a payment
bool processPayment(const Payment& payment)
{
    // Check if user exist
    User userDetails;
    if (!getUserDetails(payment.user_id, "", userDetails))
    {
        return 0;
    }

    // Check if the booking exist
    Booking bookingDetails;
    if(!getBookingDetails(payment.booking_id, bookingDetails))
    {
        return 0;
    }

    // Check if the payment date matches the booking date or start date
    if (payment.payment_date != bookingDetails.booking_date && payment.payment_date != bookingDetails.start_date)
    {
        cout << "Payment date does not match the booking date." << endl;
        return 0;
    }

    // Check if the payment amount is more than the total rental price
    if (payment.amount > bookingDetails.amt_left) {
        cout << "Payment amount exceeds the rental price." << endl;
        return 0;
    }

    // Check if the payment amount is valid
    double half_price = bookingDetails.amt_left / 2.0;
    if (payment.payment_date == bookingDetails.booking_date)
    {
        if (payment.amount < half_price)
        {
            cout << "At least half of the total rental price must be paid on the booking date." << endl;
            return 0;
        }
        else if (payment.amount < bookingDetails.total_price && bookingDetails.total_price == bookingDetails.amt_left)
        {
            double remaining_amount = bookingDetails.total_price - payment.amount;
            cout << "Remaining amount to be paid on the pickup date: $" << remaining_amount << endl;
            updateRemainingAmt(payment.booking_id, remaining_amount);
        }
        else 
        {
            cout << "Half payment already done. Next payment must be during pickup." << endl;
            return 0;
        }
    }
    else if (payment.payment_date == bookingDetails.start_date)
    {
        if (payment.amount != bookingDetails.amt_left)
        {
            cout << "Full payment is required for the car pickup" << endl;
            return 0;
        }
        bookingDetails.amt_left = 0;
    }

    string sql = "INSERT INTO payments (user_id, booking_id, amount, payment_date, payment_time) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind values to the SQL statement
    sqlite3_bind_int(stmt, 1, payment.user_id);
    sqlite3_bind_int(stmt, 2, payment.booking_id);
    sqlite3_bind_double(stmt, 3, payment.amount);
    sqlite3_bind_text(stmt, 4, payment.payment_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, payment.payment_time.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// Function to list all payments
void listPayments()
{
    string sql = "SELECT * FROM payments;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Payment Listings:" << endl;
    printPayListHeader();

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printPayDetails(stmt);
    }

    sqlite3_finalize(stmt);
}

// Function to list payments by User
bool listUserPayments(int userId)
{
    // Check if user exist
    User userDetails;
    if (!getUserDetails(userId, "", userDetails))
    {
        return 0;
    }

    string sql = "SELECT * FROM payments WHERE user_id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    sqlite3_bind_int(stmt, 1, userId);

    cout << "Payment history for user ID " << userId << ":" << endl;
    printPayListHeader();

    // Loop through the result set and print each booking's details
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printPayDetails(stmt);
    }

    sqlite3_finalize(stmt);

    return 1;
}

// Helper function to print header when listing all payments
void printPayListHeader()
{
    // Define the width for each column
    const int idWidth = 8;
    const int userIdWidth = 9;
    const int bookingIdWidth = 12;
    const int amount = 14;
    const int dateWidth = 14;

    // Print the header
    cout << left
         << setw(idWidth) << "ID"
         << setw(userIdWidth) << "User ID"
         << setw(bookingIdWidth) << "Booking ID"
         << setw(amount) << "Total Price"
         << setw(dateWidth) << "Payment Date"
         << endl;
}

// Helper function to print all payments
void printPayDetails(sqlite3_stmt* stmt)
{
    // Define the width for each column
    const int idWidth = 8;
    const int userIdWidth = 9;
    const int bookingIdWidth = 12;
    const int amountWidth = 14;
    const int dateWidth = 14;

    // Print Pay Details
    int id = sqlite3_column_int(stmt, 0);
    int user_id = sqlite3_column_int(stmt, 1);
    int booking_id = sqlite3_column_int(stmt, 2);
    double amount = sqlite3_column_double(stmt, 3);
    string payment_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

    // Print the header
    cout << left
         << setw(idWidth) << id
         << setw(userIdWidth) << user_id
         << setw(bookingIdWidth) << booking_id
         << setw(amountWidth) << amount
         << setw(dateWidth) << payment_date
         << endl;
}

// Function to delete all payments by Booking ID
bool deleteAllPayments(int bookingId, int userId)
{
    string sql = "";
    if (bookingId == 0)
    {
        sql = "DELETE FROM payments WHERE user_id = ?;";
    }
    else
    {
        sql = "DELETE FROM payments WHERE booking_id = ?;";
    }

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    if (bookingId == 0)
    {
        sqlite3_bind_int(stmt, 1, userId);
    }
    else
    {
        sqlite3_bind_int(stmt, 1, bookingId);
    }
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        cerr << "Execution of delete payments failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}
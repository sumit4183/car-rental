#include <sqlite3.h>
#include <iostream>

#include "../include/payment.h"
#include "../include/helper.h"

using namespace std;

extern sqlite3* db;

// Function to process a payment
bool processPayment(const Payment& payment)
{
    // Check if user exist
    User userDetails;
    if (!getUserDetails(payment.user_id, userDetails))
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
    if (payment.payment_date == bookingDetails.booking_date) {
        if (payment.amount < half_price) {
            cout << "At least half of the total rental price must be paid on the booking date." << endl;
            return 0;
        } else if (payment.amount < bookingDetails.total_price) {
            double remaining_amount = bookingDetails.total_price - payment.amount;
            cout << "Remaining amount to be paid on the pickup date: $" << remaining_amount << endl;
            updateRemainingAmt(payment.booking_id, remaining_amount);
        }
    } else if (payment.payment_date == bookingDetails.start_date) {
        if (payment.amount != bookingDetails.amt_left) {
            cout << "Full payment is required for the car pickup" << endl;
            return 0;
        }
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
void listPayments() {
    string sql = "SELECT * FROM payments;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Payment Listings:" << endl;
    cout << "ID\tUser ID\tBooking ID\tAmount\tPayment Date" << endl;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int user_id = sqlite3_column_int(stmt, 1);
        int booking_id = sqlite3_column_int(stmt, 2);
        double amount = sqlite3_column_double(stmt, 3);
        string payment_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        cout << id << "\t" << user_id << "\t" << booking_id << "\t" << amount << "\t" << payment_date << endl;
    }

    sqlite3_finalize(stmt);
}
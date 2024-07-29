#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <sqlite3.h>

using namespace std;

struct Payment {
    int id;
    int user_id;
    int booking_id;
    double amount;
    string payment_date;
    string payment_time;
};

bool processPayment(const Payment& payment);
void listPayments();
bool listUserPayments(int userId);
void printPayListHeader();
void printPayDetails(sqlite3_stmt* stmt);
bool deleteAllPayments(int bookingId);

#endif // PAYMENT_H
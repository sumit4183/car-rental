#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

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

#endif // PAYMENT_H
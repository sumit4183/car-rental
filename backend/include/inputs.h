#ifndef INPUTS_H
#define INPUTS_H

using namespace std;

void userInput(int choice);
void carInput(int choice);
void bookingInput(int choice);
void paymentInput(int choice);

void registerUserInput();
void loginUserInput();
void updateUserInput();
void deleteUserInput();

void addCarInput();
void editCarInput();
void filterCarsByTypeInput();
void filterCarsByRentalPriceInput();

void bookCarInput();
void cancelBookInput();
void listUserBookInput();

void processPayInput();
void listUserPayInput();

#endif // INPUTS_H
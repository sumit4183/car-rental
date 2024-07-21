#ifndef CAR_H
#define CAR_H

#include <string>
#include <sqlite3.h>

using namespace std;

struct Car {
    int id;
    std::string type;
    std::string make;
    std::string model;
    int year;
    double rental_price;
    bool available;
};

bool addCar(const Car& car);
bool editCar(const Car& car);
bool getCar(int carId, Car& car);
void listCars();
void printCarListHeader();
void printCarDetails(sqlite3_stmt* stmt);
void filterCarsByType(const string& type);
void filterCarsByRentalPrice(double minPrice, double maxPrice);

#endif // CAR_H
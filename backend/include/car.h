#ifndef CAR_H
#define CAR_H

#include <string>

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

#endif // CAR_H
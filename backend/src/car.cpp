#include <sqlite3.h>
#include <iostream>
#include <iomanip>

#include "../include/car.h"
#include "../include/helper.h"

using namespace std;

extern sqlite3* db;

// Function to add a new car
bool addCar(const Car& car)
{
    // SQL query to insert a new car record
    string sql = "INSERT INTO cars (type, make, model, year, rental_price, available) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind values to the SQL statement
    sqlite3_bind_text(stmt, 1, car.type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, car.make.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, car.model.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, car.year);
    sqlite3_bind_double(stmt, 5, car.rental_price);
    sqlite3_bind_int(stmt, 6, car.available);

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

// Function to edit an existing car
bool editCar(const Car& car)
{
    // SQL query to update an existing car record
    string sql = "UPDATE cars SET type = ?, make = ?, model = ?, year = ?, rental_price = ?, available = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind new values to the SQL statement
    sqlite3_bind_text(stmt, 1, car.type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, car.make.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, car.model.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, car.year);
    sqlite3_bind_double(stmt, 5, car.rental_price);
    sqlite3_bind_int(stmt, 6, car.available);
    sqlite3_bind_int(stmt, 7, car.id);

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

// Function to get details of a specific car
bool getCar(int carId, Car& car)
{
    string sql = "SELECT * FROM cars WHERE id = ?;";
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
        car.id = sqlite3_column_int(stmt, 0);
        car.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        car.make = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        car.model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        car.year = sqlite3_column_int(stmt, 4);
        car.rental_price = sqlite3_column_double(stmt, 5);
        car.available = sqlite3_column_int(stmt, 6);
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

// Function to list all cars
void listCars()
{
    string sql = "SELECT * FROM cars;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Print header for the car listings
    cout << "Car Listings:" << endl;
    printCarListHeader();

    // Loop through the result set and print each car's details
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printCarDetails(stmt);
        // cout << id << "\t" << type << std::setw(10) << make << std::setw(8) << model << "\t" << year << "\t" << price << "\t" << (available ? "Yes" : "No") << endl;
    }

    sqlite3_finalize(stmt);
}

// Function to list cars by type
void filterCarsByType(const string& type)
{
    string sql = "SELECT * FROM cars WHERE type = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, type.c_str(), -1, SQLITE_STATIC);

    cout << "Filtered Car Listings by Type (" << type << "):" << endl;
    printCarListHeader(); // Assuming you have this function for header printing

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printCarDetails(stmt); // Assuming you have this function for printing details
    }

    sqlite3_finalize(stmt);
}

// Function to list cars by Rental Price Range
void filterCarsByRentalPrice(double minPrice, double maxPrice)
{
    string sql = "SELECT * FROM cars WHERE rental_price BETWEEN ? AND ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_double(stmt, 1, minPrice);
    sqlite3_bind_double(stmt, 2, maxPrice);

    cout << "Filtered Car Listings by Rental Price Range (" << minPrice << " - " << maxPrice << "):" << endl;
    printCarListHeader();

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printCarDetails(stmt);
    }

    sqlite3_finalize(stmt);
}

// Helper function to print Header when listing cars
void printCarListHeader()
{
    // Define the width for each column
    const int idWidth = 8;
    const int typeWidth = 8;
    const int makeWidth = 10;
    const int modelWidth = 10;
    const int yearWidth = 8;
    const int priceWidth = 8;
    const int availWidth = 10;

    // Print the header
    std::cout << std::left 
    << std::setw(idWidth) << "ID" 
    << std::setw(typeWidth) << "Type" 
    << std::setw(makeWidth) << "Make" 
    << std::setw(modelWidth) << "Model" 
    << std::setw(yearWidth) << "Year" 
    << std::setw(priceWidth) << "Price" 
    << std::setw(availWidth) << "Available" 
    << std::endl;
}

// Helper function to list car details
void printCarDetails(sqlite3_stmt* stmt)
{
    // Define the width for each column
    const int idWidth = 8;
    const int typeWidth = 8;
    const int makeWidth = 10;
    const int modelWidth = 10;
    const int yearWidth = 8;
    const int priceWidth = 8;
    const int availWidth = 10;

    // Print Car Details
    int id = sqlite3_column_int(stmt, 0);
    string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    string make = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    string model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    int year = sqlite3_column_int(stmt, 4);
    double price = sqlite3_column_double(stmt, 5);
    bool available = sqlite3_column_int(stmt, 6);
    cout << left 
        << setw(idWidth) << id
        << setw(typeWidth) << type
        << setw(makeWidth) << make 
        << setw(modelWidth) << model
        << setw(yearWidth) << year 
        << setw(priceWidth) << price 
        << setw(availWidth) << (available ? "Yes" : "No")
        << endl;
}

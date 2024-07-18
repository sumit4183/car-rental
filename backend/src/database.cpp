#include <sqlite3.h>
#include <iostream>
#include "../include/database.h"

using namespace std;
sqlite3* db;            // Pointer to SQLite database

// Function to open the database connection and displaying result
bool openDatabase(const char* filename)
{
    int rc = sqlite3_open(filename, &db);
    if (rc)
    {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    else
    {
        cout << "Opened database successfully" << endl;
        return true;
    }
}

// Function to close the database connection
void closeDatabase()
{
    sqlite3_close(db);
}

// Function to initialize the database by creating the users table if it doesn't exist
bool initializeDatabase()
{
    // SQL statement to create the users table
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY NOT NULL,
            username TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL,
            name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE
        );

        CREATE TABLE IF NOT EXISTS cars (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            type TEXT NOT NULL,
            make TEXT NOT NULL,
            model TEXT NOT NULL,
            year INTEGER NOT NULL,
            rental_price REAL NOT NULL,
            available INTEGER NOT NULL DEFAULT 1
        );

        CREATE TABLE IF NOT EXISTS bookings (
            id INTEGER PRIMARY KEY NOT NULL,
            user_id INTEGER NOT NULL,
            car_id INTEGER NOT NULL,
            start_date TEXT NOT NULL,
            end_date TEXT NOT NULL,
            start_time TEXT NOT NULL,
            end_time TEXT NOT NULL,
            booking_date TEXT NOT NULL,
            booking_time TEXT NOT NULL,
            total_price REAL NOT NULL,
            amt_left REAL NOT NULL,
            FOREIGN KEY(user_id) REFERENCES users(id),
            FOREIGN KEY(car_id) REFERENCES cars(id)
        );

        CREATE TABLE IF NOT EXISTS payments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            booking_id INTEGER NOT NULL,
            amount REAL NOT NULL,
            payment_date TEXT NOT NULL,
            payment_time TEXT NOT NULL,
            FOREIGN KEY(user_id) REFERENCES users(id),
            FOREIGN KEY(booking_id) REFERENCES bookings(id)
        );
    )";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);      // Execute the SQL statement
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    else
    {
        cout << "Table created successfully" << endl;
        return true;
    }
}
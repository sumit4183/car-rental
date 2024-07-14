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
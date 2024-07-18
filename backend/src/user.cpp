#include <sqlite3.h>
#include <iostream>
#include <string>
#include <regex>

#include "../include/user.h"
#include "../include/helper.h"

using namespace std;

extern sqlite3* db;

// Function to validate email format
bool isValidEmail(const string& email)
{
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.(\w+))+)");
    return regex_match(email, pattern);
}

void printErr(const char* err)
{
    const char* errorMessages[][2] = {
        { "UNIQUE constraint failed: users.username", "Username already exists. Please choose a different username." },
        { "UNIQUE constraint failed: users.email", "Email already exists. Please choose a different email." }
    };

    for (const auto& error : errorMessages)
    {
        if (strstr(err, error[0]) != nullptr)
        {
            cout << error[1] << endl;
            return;
        }
    }
}

// Function to register a new user
bool registerUser(const string& username, const string& password, const string& name, const string& email)
{
    if (!isValidEmail(email))
    {
        cout << "Invalid email format. Please enter a valid email (example@company.com)." << endl;
        return false;
    }

    // Find the smallest available ID for the new user
    string findIdSql = R"(
        SELECT id + 1
        FROM users u1
        WHERE NOT EXISTS (SELECT 1 FROM users u2 WHERE u2.id = u1.id + 1)
        ORDER BY u1.id
        LIMIT 1;
    )";
    sqlite3_stmt* findIdStmt;
    int rc = sqlite3_prepare_v2(db, findIdSql.c_str(), -1, &findIdStmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    int nextId = 0;
    rc = sqlite3_step(findIdStmt);      // Execute the SQL statement
    if (rc == SQLITE_ROW)       // If a row is returned, get the next available ID
    {
        nextId = sqlite3_column_int(findIdStmt, 0);
    }
    else
    {
        // If no gaps are found, findIdSql returns no rows, and we should start from the highest ID + 1
        string maxIdSql = "SELECT COALESCE(MAX(id), 0) + 1 FROM users;";
        sqlite3_stmt* maxIdStmt;
        rc = sqlite3_prepare_v2(db, maxIdSql.c_str(), -1, &maxIdStmt, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        rc = sqlite3_step(maxIdStmt);
        if (rc == SQLITE_ROW)       // If a row is returned, get the next available ID
        {
            nextId = sqlite3_column_int(maxIdStmt, 0);
        }
        sqlite3_finalize(maxIdStmt);
    }
    sqlite3_finalize(findIdStmt);

    // Insert the new user with the calculated ID
    string sql = "INSERT INTO users (id, username, password, name, email) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind values to the SQL statement
    sqlite3_bind_int(stmt, 1, nextId);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);  // Consider hashing the password
    sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        if (rc == SQLITE_CONSTRAINT)
        {
            const char* errMsg = sqlite3_errmsg(db);
            printErr(errMsg);
            return false;
        }
        cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// Function to log in a user
bool loginUser(const string& username, const string& password)
{
    string sql = "SELECT password FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind the username to the SQL statement
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        // Retrieve the stored password from the database
        string storedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);

        // Here, you would compare the hashed passwords in a real application
        return storedPassword == password;
    }
    else
    {
        cerr << "No such user found" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

// Function to update a user's profile
bool updateUserProfile(const string& username, const string& name, const string& password) 
{
    if(!checkUser(username))
    {
        return false;
    }

    string sql = "UPDATE users SET name = ?, password = ? WHERE username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind new values to the SQL statement
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, username.c_str(), -1, SQLITE_STATIC);

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

// Function to delete a user
bool deleteUser(const string& username)
{
    if(!checkUser(username))
    {
        return false;
    }

    string sql = "DELETE FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    

    if (rc != SQLITE_OK)
    {
        cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind the username to the SQL statement
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

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
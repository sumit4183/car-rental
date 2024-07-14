#ifndef USER_H
#define USER_H

#include <string>

bool registerUser(const std::string& username, const std::string& password, const std::string& name, const std::string& email);
bool loginUser(const std::string& username, const std::string& password);
bool updateUserProfile(const std::string& username, const std::string& name, const std::string& password);
bool deleteUser(const std::string& username);

#endif // USER_H
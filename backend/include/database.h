#ifndef DATABASE_H
#define DATABASE_H

bool openDatabase(const char* filename);
void closeDatabase();
bool initializeDatabase();

#endif // DATABASE_H
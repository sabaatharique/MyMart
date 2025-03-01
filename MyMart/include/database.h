#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sqlite3.h>

using namespace std;

class Database
{
    public:
        Database();
        ~Database();

        bool openDatabase(string fileName);

        sqlite3* getDatabase();

        bool executeQuery(string query);

        bool initialiseDatabase();

        bool displayTable(string table);

        bool closeDatabase();

        sqlite3_stmt* searchFromTable(Database& db, int ID, const string& table);

        sqlite3_stmt* fetchQuery(string query);

    protected:

    private:
        sqlite3 *DB;
};

#endif // DATABASE_H

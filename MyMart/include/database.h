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

        bool displayTable(string table);

        void closeDatabase();

    protected:

    private:
        sqlite3 *DB;
};

#endif // DATABASE_H

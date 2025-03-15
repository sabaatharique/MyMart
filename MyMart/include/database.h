#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <curses.h>
#include <vector>
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

        void display(const vector<string> &columnNames, const vector<vector<string>> &tableContents);

        bool displayTable(string table, int *next_line = NULL);

        bool closeDatabase();

        sqlite3_stmt* searchFromTable(Database& db, int ID, const string& table);

        sqlite3_stmt* fetchQuery(string query);

    protected:

    private:
        sqlite3 *DB;
};

#endif // DATABASE_H

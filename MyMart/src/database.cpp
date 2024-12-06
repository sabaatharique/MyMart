#include "database.h"

Database::Database() {}

Database::~Database() {}

bool Database::openDatabase(string fileName)
{
    int exitCode = sqlite3_open(fileName.c_str(), &DB);

    if (exitCode) {
        cerr << "Error opening " << fileName << " : " << sqlite3_errmsg(DB) << endl;
        return false;
    }
    cout << "Successfully opened " << fileName << endl;
    return true;
}

sqlite3* Database::getDatabase()
{
    return DB;
}


// used mainly to update, insert into, or alter tables
bool Database::executeQuery(string query)
{
    char *errorMsg;
    int exitCode = sqlite3_exec(DB, query.c_str(), NULL, 0, &errorMsg);

    if (exitCode != SQLITE_OK) {
        cerr << "SQL error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        return false;
    }
    return true;
}

// used to display all results of a table after query
bool Database::displayTable(string query)
{
    sqlite3_stmt *stmt;
    int exitCode = sqlite3_prepare_v2(DB, query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(DB) << endl;
        return false;
    }

    // get number of columns and print column names first
    int columns = sqlite3_column_count(stmt);
    cout << left;
    for (int i = 0; i < columns; i++){
        string colName = sqlite3_column_name(stmt, i);
        cout << setw(25) << colName;
    }

    cout << endl;
    cout << string(25 * columns, '-') << endl;

    while(sqlite3_step(stmt) == SQLITE_ROW){
        for (int i = 0; i < columns; i++){
            const char *text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            cout << setw(25) << (text ? text : "NULL");
        }
        cout << endl;
    }
    sqlite3_finalize(stmt);
    return true;
}


void Database::closeDatabase()
{
    sqlite3_close(DB);
}



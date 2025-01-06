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

bool Database::initialiseDatabase()
{
    if(!openDatabase("supermarket.db"))
        return false;

    string sql = "CREATE TABLE PRODUCTS("
                 "ID INT PRIMARY KEY NOT NULL,"
                 "NAME CHAR(25) NOT NULL,"
                 "SELLING_PRICE REAL NOT NULL,"
                 "BUYING_COST REAL NOT NULL,"
                 "IN_STOCK REAL NOT NULL,"
                 "EXPIRY_DATE DATE);";
    if(!executeQuery(sql))
        return false;

    sql = "INSERT INTO PRODUCTS VALUES(21000, 'APPLES RED', 150, 100, 50, '2024-12-19');"
          "INSERT INTO PRODUCTS VALUES(10001, 'SCISSORS', 500, 400, 0, NULL);"
          "INSERT INTO PRODUCTS VALUES(21002, 'BANANAS', 125, 95, 80, '2024-12-26');"
          "INSERT INTO PRODUCTS VALUES(10003, 'COLOUR PENCILS', 275, 240, 15, NULL);"
          "INSERT INTO PRODUCTS VALUES(22004, 'MILK', 100, 80, 60, '2024-12-25');"
          "INSERT INTO PRODUCTS VALUES(10005, 'BLACK PEN 12 PACK', 120, 100, 18, NULL);"
          "INSERT INTO PRODUCTS VALUES(10006, 'GRAPES GREEN', 100, 85, 60, '2024-12-22');"
          "INSERT INTO PRODUCTS VALUES(10007, 'WHITE PAPER 500', 480, 400, 12, NULL);"
          "INSERT INTO PRODUCTS VALUES(10008, 'TOMATOES', 80, 70, 60, '2024-12-10');";
    if(!executeQuery(sql))
        return false;

    sql = "CREATE TABLE EMPLOYEES("
          "ID INT PRIMARY KEY NOT NULL,"
          "NAME CHAR(25) NOT NULL,"
          "TYPE CHAR(15) CHECK (TYPE IN ('MANAGER', 'CASHIER', 'STOCK CLERK')),"
          "SALARY REAL NOT NULL);";
    if(!executeQuery(sql))
        return false;

    sql = "INSERT INTO EMPLOYEES VALUES(1130, 'SABA ATHARIQUE', 'MANAGER', 40500);"
          "INSERT INTO EMPLOYEES VALUES(1110, 'RIDITA ALAM', 'CASHIER', 35750);"
          "INSERT INTO EMPLOYEES VALUES(1134, 'MISHKAT AHMED KHAN', 'STOCK CLERK', 27500);";
    if(!executeQuery(sql))
        return false;

    sql = "CREATE TABLE CUSTOMERS("
          "ID INT PRIMARY KEY NOT NULL,"
          "NAME CHAR(25) NOT NULL,"
          "TYPE CHAR(10) CHECK (TYPE IN ('LOYAL', 'REGULAR')),"
          "TOTAL_SPENT REAL);";
    if(!executeQuery(sql))
        return false;

    sql = "INSERT INTO CUSTOMERS VALUES(220041117, 'DIDHITI NAHID', 'REGULAR', 675);"
          "INSERT INTO CUSTOMERS VALUES(220041101, 'ANJIM HOSSAIN', 'REGULAR', 20);"
          "INSERT INTO CUSTOMERS VALUES(220041122, 'RAHATUT TAHRIM', 'LOYAL', 1250);"
          "INSERT INTO CUSTOMERS VALUES(120041137, 'FAISAL HUSSAIN', 'LOYAL', 5675);";
    if(!executeQuery(sql))
        return false;

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

sqlite3_stmt* Database::searchFromTable(Database& db, int ID, const string table)
{
    string query = "SELECT * FROM " + table + " WHERE ID = ?;";
    sqlite3_stmt* stmt = nullptr;

    int exitCode = sqlite3_prepare_v2(db.getDatabase(), query.c_str(), -1, &stmt, NULL);
    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return nullptr;
    }

    exitCode = sqlite3_bind_int(stmt, 1, ID);
    if (exitCode != SQLITE_OK) {
        cerr << "Could not bind parameter: " << sqlite3_errmsg(db.getDatabase()) << endl;
        sqlite3_finalize(stmt);
        return nullptr;
    }

    return stmt;
}


bool Database::closeDatabase()
{
    string sql = "DROP TABLE PRODUCTS;";
    if(!executeQuery(sql))
        return false;

    sql = "DROP TABLE CUSTOMERS;";
    if(!executeQuery(sql))
        return false;

    sql = "DROP TABLE EMPLOYEES;";
    if(!executeQuery(sql))
        return false;

    sqlite3_close(DB);
    return true;
}



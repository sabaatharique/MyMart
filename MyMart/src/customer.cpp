#include "customer.h"

Customer::Customer(string x, int n) : CustomerName(x), CustomerID(n), TotalAmountSpent(0) {}

Customer::Customer() : TotalAmountSpent(0) {}

Customer::~Customer() {}

string Customer::GetCustomerName()
{
    return CustomerName;
}

void Customer::SetCustomerName(string name)
{
    CustomerName = name;
}
int Customer::GetCustomerID()
{
    return CustomerID;
}

void Customer::SetCustomerID(int ID)
{
    CustomerID = ID;
}

double Customer::GetTotalAmountSpent()
{
    return TotalAmountSpent;
}

void Customer::SetTotalAmountSpent(double val)
{
    TotalAmountSpent = val;
}

bool Customer::GetCustomerByID(Database& db, int ID)
{
    sqlite3_stmt* stmt = db.searchFromTable(db, ID, "CUSTOMERS");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double total_spent = sqlite3_column_double(stmt, 3);

        this->CustomerID = id;
        this->CustomerName = name;
        this->TotalAmountSpent = total_spent;
    }
    else {
        sqlite3_finalize(stmt);
        cerr << "No customer found with ID: " << ID << endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Customer::AddCustomer(Database& db)
{
    string query = "INSERT INTO CUSTOMERS VALUES(" + to_string(CustomerID) + ", '" + CustomerName + "', 'REGULAR', " + to_string(TotalAmountSpent) + ");";

    if(!db.executeQuery(query))
        return false;

    return true;
}

bool Customer::GenerateNewID(Database& db)
{
    string query = "SELECT COUNT(*) FROM CUSTOMERS;";

    sqlite3_stmt *stmt;
    int exitCode = sqlite3_prepare_v2(db.getDatabase(), query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return false;
    }

    exitCode = sqlite3_step(stmt);
    if (exitCode == SQLITE_ROW) {
        int totalCustomers = sqlite3_column_int(stmt, 0);

        // maximum capacity
        if (totalCustomers > 9999998)
            return false;

        // new ID is in numerical order, 1 + total number of customers
        SetCustomerID(totalCustomers + 1 + 10000000);
    }
    else {
        cerr << "Could not execute query: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}


bool Customer::UpdateTotalAmountSpent(Database& db)
{
    string query = "UPDATE CUSTOMERS SET TOTAL_SPENT = " + to_string(TotalAmountSpent) + " WHERE ID = " + to_string(CustomerID) + ";";
    return db.executeQuery(query);
}

bool Customer::UpdateCustomerStatus(Database& db)
{
    // regular to loyal conversion
    if(TotalAmountSpent >= 10000) {
        string query = "UPDATE CUSTOMERS SET TYPE = 'LOYAL' WHERE ID = " + to_string(CustomerID) + ";";
        if(!db.executeQuery(query)) {
            return false;
        }

        // change ID to start with 2
        string newID = to_string(CustomerID);
        newID[0] = '2';

        query = "UPDATE CUSTOMERS SET ID = " + newID + " WHERE ID = " + to_string(CustomerID) + ";";
        if(!db.executeQuery(query)) {
            return false;
        }
    }
    return true;
}

int Customer::DisplayDetails(int start_line)
{
    mvwprintw(stdscr, start_line, 2, "Customer ID: ");
    mvwprintw(stdscr, start_line, 2 + 13, to_string(CustomerID).c_str());
    mvwprintw(stdscr, start_line + 1, 2, "Customer name: ");
    mvwprintw(stdscr, start_line + 1, 2 + 15, CustomerName.c_str());
    mvwprintw(stdscr, start_line + 2, 2, "Total Amount Spent: ");
    mvwprintw(stdscr, start_line + 2, 2 + 20, to_string(TotalAmountSpent).c_str());

    return start_line + 3;
}
